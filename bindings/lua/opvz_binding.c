#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "opvz.h"

int luaopen_opvz(lua_State *L)
{
	lua_register(L, "hello", hello);
	return 0;
}
