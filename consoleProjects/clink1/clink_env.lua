--[[
   Copyright (c) 2012 Martin Ridgers

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
]]--

--------------------------------------------------------------------------------
special_env_vars = {
    "cd", "date", "time", "random", "errorlevel",
    "cmdextversion", "cmdcmdline", "highestnumanodenumber"
}

--------------------------------------------------------------------------------
function env_vars_match_generator(text, first, last)
    -- Use this match generator if out text starts with a % or "%
    if not text:find("^%%") then
        return false
    end
    
    text = text:sub(2):lower()
    local text_len = #text
    for _, name in ipairs(clink.getenvvarnames()) do
        if name:sub(1, text_len):lower() == text then
            clink.add_match('%'..name..'%')
        end
    end

    for _, name in ipairs(special_env_vars) do
        if name:sub(1, text_len):lower() == text then
            clink.add_match('%'..name..'%')
        end
    end

    return true
end

--------------------------------------------------------------------------------
clink.register_match_generator(env_vars_match_generator, 100)
