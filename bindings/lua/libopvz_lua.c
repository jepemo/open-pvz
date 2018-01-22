/**
 * open-pvz - Tower Defense Game Engine inspired by "Plantz Vz Zombiez",
 *            implemented in C with differents bindings for other languages.
 *
 * Copyright (C) 2017-present Jeremies Pérez Morata
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <unistd.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "opvz.h"



/* Register this file's functions with the
 * luaopen_libraryname() function, where libraryname
 * is the name of the compiled .so output. In other words
 * it's the filename (but not extension) after the -o
 * in the cc command.
 *
 * So for instance, if your cc command has -o power.so then
 * this function would be called luaopen_power().
 *
 * This function should contain lua_register() commands for
 * each function you want available from Lua.
 *
*/

//int luaopen_opvzlib(lua_State *L){
//	lua_register(
//			L,               /* Lua state variable */
//			"square",        /* func name as known in Lua */
//			isquare          /* func name in this file */
//			);
//	lua_register(L,"cube",icube);
//	return 0;
//}

static int sleep_c(lua_State *L){
	long secs = lua_tointeger(L, -1);
	sleep(secs);
	return 0;                  /* No items returned */
}

static int icube(lua_State *L){
	float rtrn = lua_tonumber(L, -1);
	// printf("Top of cube(), number=%f\n",rtrn);
	lua_pushnumber(L,rtrn*rtrn*rtrn);
	return 1;
}

/*
static int ihello(lua_State *L){
  // printf("ihello!");
	float rtrn = lua_tonumber(L, -1);
	lua_pushnumber(L,hello(rtrn));
  //lua_pushnumber(L,rtrn*rtrn*rtrn);
	return 1;
}
*/

static int icreate_new_level_default(lua_State *L) {
  // lua_push
  return 1;
}


int luaopen_libopvz_lua(lua_State *L)
{
	// lua_register(L, "hello", ihello);
  lua_register(L, "cube",  icube);
  lua_register(L, "sleep", sleep_c);
	return 0;
}
