/* Copyright (c) 2012 Martin Ridgers
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "clink_pch.h"

//------------------------------------------------------------------------------
void                get_dll_dir(char*, int);
void                get_config_dir(char*, int);
void                str_cat(char*, const char*, int);
static int          reload_lua_state(int count, int invoking_key);

extern int          g_match_palette[3];
static lua_State*   g_lua = NULL;

//------------------------------------------------------------------------------
static void load_lua_script(const char* script)
{
    if (luaL_dofile(g_lua, script) != 0)
    {
        const char* error_msg = lua_tostring(g_lua, -1);
        fputs(error_msg, stderr);
        fputs("\n", stderr);
        lua_pop(g_lua, 1);
    }
}

//------------------------------------------------------------------------------
static void load_lua_scripts(const char* path)
{
    char old_dir[1024];
    HANDLE find;
    WIN32_FIND_DATA fd;

    GetCurrentDirectory(sizeof(old_dir), old_dir);
    SetCurrentDirectory(path);

    find = FindFirstFile("*.lua", &fd);
    while (find != INVALID_HANDLE_VALUE)
    {
        if (_stricmp(fd.cFileName, "clink_core.lua") != 0)
        {
            load_lua_script(fd.cFileName);
        }

        if (FindNextFile(find, &fd) == FALSE)
        {
            FindClose(find);
            break;
        }
    }

    SetCurrentDirectory(old_dir);
}

//------------------------------------------------------------------------------
static int find_files(lua_State* state)
{
    HANDLE find;
    WIN32_FIND_DATA fd;
    const char* mask;
    int i = 1;

    if (lua_gettop(state) == 0)
    {
        return 0;
    }

    if (lua_isnil(state, 1))
    {
        return 0;
    }

    mask = lua_tostring(state, 1);
    lua_createtable(state, 0, 0);

    find = FindFirstFile(mask, &fd);
    while (find != INVALID_HANDLE_VALUE)
    {
        lua_pushstring(state, fd.cFileName);
        lua_rawseti(state, -2, i++);

        if (FindNextFile(find, &fd) == FALSE)
        {
            FindClose(find);
            break;
        }
    }

    return 1;
}

//------------------------------------------------------------------------------
static int get_env(lua_State* state)
{
    unsigned size;
    char* name;
    char* buffer;

    if (lua_gettop(state) == 0)
    {
        return 0;
    }

    if (lua_isnil(state, 1))
    {
        return 0;
    }

    name = lua_tostring(state, 1);
    size = GetEnvironmentVariable(name, NULL, 0);
    
    buffer = (char*)malloc(size);
    GetEnvironmentVariable(name, buffer, size);
    lua_pushstring(state, buffer);
    free(buffer);
    
    return 1;
}

//------------------------------------------------------------------------------
static int get_env_var_names(lua_State* state)
{
    char* env_strings;
    int i = 1;

    lua_createtable(state, 0, 0);
    env_strings = GetEnvironmentStrings();
    if (env_strings != NULL)
    {
        char* string = env_strings;

        while (*string)
        {
            char* eq = strchr(string, L'=');
            if (eq != NULL)
            {
                size_t length = eq - string + 1;
                char name[1024];

                length = length < sizeof_array(name) ? length : sizeof_array(name);
                --length;
                strncpy(name, string, length);
                name[length] = L'\0';

                lua_pushstring(state, name);
                lua_rawseti(state, -2, i++);
            }

            string += strlen(string) + 1;
        }

        FreeEnvironmentStrings(env_strings);
    }

    return 1;
}

//------------------------------------------------------------------------------
static int set_palette(lua_State* state)
{
    int col, i;

    for (i = 0; i < lua_gettop(state) && i < sizeof_array(g_match_palette); ++i)
    {
        col = -1;
        if (lua_isnil(state, i + 1) == 0)
        {
            col = lua_tointeger(state, i + 1);
        }

        g_match_palette[i] = col;
    }

    return 0;
}

//------------------------------------------------------------------------------
void initialise_lua()
{
    static int once = 0;
    int i;
    char buffer[1024];
    struct luaL_Reg clink_native_methods[] = {
        { "findfiles", find_files },
        { "getenvvarnames", get_env_var_names },
        { "setpalette", set_palette },
        { "getenv", get_env },
        { NULL, NULL }
    };

    if (g_lua != NULL)
    {
        return;
    }

    // Initialise Lua.
    g_lua = luaL_newstate();
    luaL_openlibs(g_lua);

    // Load all the .lua files alongside the dll and in the appdata folder.
    get_dll_dir(buffer, sizeof(buffer));
    i = (int)strlen(buffer);

    str_cat(buffer, "/clink_core.lua", sizeof(buffer));
    load_lua_script(buffer);

    buffer[i] = '\0';
    load_lua_scripts(buffer);

    get_config_dir(buffer, sizeof(buffer));
    load_lua_scripts(buffer);

    lua_getglobal(g_lua, "clink");
    luaL_setfuncs(g_lua, clink_native_methods, 0);
    lua_pop(g_lua, 1);

    if (!once)
    {
        rl_add_funmap_entry("reload-lua-state", reload_lua_state);
        once = 1;
    }
}

//------------------------------------------------------------------------------
void shutdown_lua()
{
    if (g_lua == NULL)
    {
        return;
    }

    lua_close(g_lua);
    g_lua = NULL;
}

//------------------------------------------------------------------------------
char** lua_generate_matches(const char* text, int start, int end)
{
    int match_count;
    int use_matches;
    int i;
    char** matches = NULL;

    // Expose some of the readline state to lua.
    lua_pushstring(g_lua, rl_line_buffer);
    lua_setglobal(g_lua, "rl_line_buffer");

    lua_pushinteger(g_lua, rl_point + 1);
    lua_setglobal(g_lua, "rl_point");

    // Call to Lua to generate matches.
    lua_getglobal(g_lua, "clink");
    lua_pushliteral(g_lua, "generate_matches");
    lua_rawget(g_lua, -2);

    lua_pushstring(g_lua, text);
    lua_pushinteger(g_lua, start + 1);
    lua_pushinteger(g_lua, end + 1);
    if (lua_pcall(g_lua, 3, 1, 0) != 0)
    {
        puts(lua_tostring(g_lua, -1));
        lua_pop(g_lua, 2);
        return NULL;
    }

    use_matches = lua_toboolean(g_lua, -1);
    lua_pop(g_lua, 1);

    if (use_matches == 0)
    {
        lua_pop(g_lua, 1);
        return NULL;
    }

    // Collect matches from Lua.
    lua_pushliteral(g_lua, "matches");
    lua_rawget(g_lua, -2);

    match_count = lua_rawlen(g_lua, -1);
    if (match_count > 0)
    {
        matches = (char**)calloc(match_count + 1, sizeof(*matches));
        for (i = 0; i < match_count; ++i)
        {
            const char* match;

            lua_rawgeti(g_lua, -1, i + 1);
            match = lua_tostring(g_lua, -1);
            matches[i] = malloc(strlen(match) + 1);
            strcpy(matches[i], match);

            lua_pop(g_lua, 1);
        }
    }
    lua_pop(g_lua, 2);

    return matches;
}

//------------------------------------------------------------------------------
static int reload_lua_state(int count, int invoking_key)
{
    shutdown_lua();
    initialise_lua();
    return 1;
}
