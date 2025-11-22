/*
 * LuaCompat.h
 *
 *  Library that tries to hide almost all diferences
 *  between Lua versions
 *
 */

// pragmas added by Nick Gammon
#pragma warning ( disable : 4100)  // unreferenced formal parameter
#pragma warning ( disable : 4189)  // warning C4189: 'iVersion' : local variable is initialized but not referenced
#pragma warning ( disable : 4244)  // conversion from 'int' to 'unsigned short', possible loss of data
#pragma warning ( disable : 4310)  // cast truncates constant value
#pragma warning ( disable : 4245)  // conversion from 'long' to 'unsigned long', signed/unsigned mismatch
#pragma warning ( disable : 4127)  // conditional expression is constant
#pragma warning ( disable : 4701)  // local variable 'xxx' may be used without having been initialized
#pragma warning ( disable : 4702)  // unreachable code
#pragma warning ( disable : 4710)  // function 'x' not inlined

#ifndef __LUACOMPAT_H
#define __LUACOMPAT_H

#include "tStringBuffer.h"

int luaCompat_call(lua_State* L, int nargs, int nresults);
int luaCompat_call(lua_State* L, int nargs, int nresults, tStringBuffer& ErrMsg);

void luaCompat_newLuaType(lua_State* L, const char* module_name, const char* name);
void luaCompat_pushTypeByName(lua_State* L, const char* module, const char* type_name);
int luaCompat_newTypedObject(lua_State* L, void* object);
int luaCompat_isOfType(lua_State* L, const char* module, const char* type);
void luaCompat_getType(lua_State* L, int index);
const void* luaCompat_getType2(lua_State* L, int index);

void* luaCompat_getPointer(lua_State* L, int index);

void luaCompat_moduleCreate(lua_State* L, const char* module);
void luaCompat_moduleSet(lua_State* L, const char* module, const char* key);
void luaCompat_moduleGet(lua_State* L, const char* module, const char* key);

int luaCompat_checkTagToCom(lua_State *L, int luaval);

#ifdef __cplusplus
extern "C"
{
#endif
#include <lua.h>
#include <lauxlib.h>
#ifdef __cplusplus
}
#endif

#define lua_boxpointer(L,u) \
    (*(void **)(lua_newuserdata(L, sizeof(void *))) = (u)) 

#if LUA_VERSION_NUM >= 502 /* Lua >= 5.2 */

#ifndef lua_objlen
#  define lua_objlen lua_rawlen
#endif

#ifndef lua_strlen
#  define lua_strlen lua_rawlen
#endif

#ifndef lua_equal
#  define lua_equal(L,idx1,idx2) lua_compare(L,(idx1),(idx2),LUA_OPEQ)
#endif

#ifndef luaL_register
void luaL_register (lua_State *L, const char *libname, const luaL_Reg *l);
#endif

#endif

#endif /* __LUACOMPAT_H */
