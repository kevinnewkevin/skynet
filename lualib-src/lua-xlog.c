#define LUA_LIB

#include <lua.h>
#include <lauxlib.h>

#include "skynet_xlogger.h"

static int 
ldebug(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	char msg[LOG_MAX] = { 0 };
	snprintf(msg, sizeof(msg), "[DEBUG] %s\n", s);
	skynet_xlogger_append(msg, strlen(msg));
	return 0;
}

static int
linfo(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	char msg[LOG_MAX] = { 0 };
	snprintf(msg, sizeof(msg), "[INFO] %s\n", s);
	skynet_xlogger_append(msg, strlen(msg));
	return 0;
}

static int 
lwarning(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	char msg[LOG_MAX] = { 0 };
	snprintf(msg, sizeof(msg), "[WARNING] %s\n", s);
	skynet_xlogger_append(msg, strlen(msg));
	return 0;
}

static int 
lerror(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	char msg[LOG_MAX] = { 0 };
	snprintf(msg, sizeof(msg), "[ERROR] %s\n", s);
	skynet_xlogger_append(msg, strlen(msg));
	return 0;
}

static int 
lfatal(lua_State *L) {
	size_t l = 0;
	const char * s = luaL_checklstring(L, 1, &l);
	char msg[LOG_MAX] = { 0 };
	snprintf(msg, sizeof(msg), "[FATAL] %s\n", s);
	skynet_xlogger_append(msg, strlen(msg));
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
