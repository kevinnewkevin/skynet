#define LUA_LIB

#include <lua.h>
#include <lauxlib.h>

#include "skynet_xlogger.h"

static int 
ldebug(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	skynet_xlogger_append(LOG_DEBUG, s, l);
	return 0;
}

static int
linfo(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	skynet_xlogger_append(LOG_INFO, s, l);
	return 0;
}

static int 
lwarning(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	skynet_xlogger_append(LOG_WARNING, s, l);
	return 0;
}

static int 
lerror(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	skynet_xlogger_append(LOG_ERROR, s, l);
	return 0;
}

static int 
lfatal(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	skynet_xlogger_append(LOG_FATAL, s, l);
	return 0;
}

LUAMOD_API int 
luaopen_skynet_xlog_core(lua_State *L) {
	luaL_checkversion(L);
	luaL_Reg l[] =
	{
		{ "debug", ldebug },
		{ "info", linfo },
		{ "warning", lwarning },
		{ "error", lerror },
		{ "fatal", lfatal },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);

	return 1;
}
