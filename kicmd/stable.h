#pragma once

//build directly
#ifdef BUILD_KI_FRAMEWORK_STATIC_BUILD
#    define KI_CMD_EXPORT
#    define KI_CORE_EXPORT
#    define KI_COROUTINE_EXPORT
#    define KI_GRAPHICS_EXPORT
#    define KI_GUI_EXPORT
#    define KI_LUABIND_EXPORT
#    define EASTL_API
#    define KI_NETWORK_EXPORT
#    define KI_APP_EXPORT
#else
//build dll
#  ifdef BUILD_KI_CMD
#    define KI_CMD_EXPORT __declspec( dllexport )
#  else
#    define KI_CMD_EXPORT __declspec( dllimport )
#  endif  // BUILD_KI_CMD

#  ifdef BUILD_KI_CORE
#    define KI_CORE_EXPORT __declspec( dllexport )
#  else
#    define KI_CORE_EXPORT __declspec( dllimport )
#  endif // BUILD_KI_CORE

#  ifdef BUILD_KI_COROUTINE
#    define KI_COROUTINE_EXPORT __declspec( dllexport )
#  else
#    define KI_COROUTINE_EXPORT __declspec( dllimport )
#  endif // BUILD_KI_COROUTINE

#  ifdef BUILD_KI_GRAPHICS
#    define KI_GRAPHICS_EXPORT __declspec( dllexport )
#  else
#    define KI_GRAPHICS_EXPORT __declspec( dllimport )
#  endif // BUILD_KI_GRAPHICS

#  ifdef BUILD_KI_GUI
#    define KI_GUI_EXPORT __declspec( dllexport )
#  else
#    define KI_GUI_EXPORT __declspec( dllimport )
#  endif // BUILD_KIT_GUI

#  ifdef BUILD_KI_LUABIND
#    define KI_LUABIND_EXPORT __declspec( dllexport )
#    define LUA_BUILD_AS_DLL
#    define LUA_LIB
#  else
#    define KI_LUABIND_EXPORT __declspec( dllimport )
#    define LUA_BUILD_AS_DLL
#  endif // BUILD_KI_LUABIND

#  ifdef BUILD_KI_NETWORK
#    define KI_NETWORK_EXPORT __declspec( dllexport )
#  else
#    define KI_NETWORK_EXPORT __declspec( dllimport )
#  endif// BUILD_KI_NETWORK

#  ifdef BUILD_KI_APP
#    define KI_APP_EXPORT __declspec( dllexport )
#  else
#    define KI_APP_EXPORT __declspec( dllimport )
#  endif

#endif