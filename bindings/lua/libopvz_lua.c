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
#include "libopvz_lua.h"
#include "opvz.h"


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
    Level * new_level = level_new_default();
    
    global_levels[current_level_pos] = new_level;

    current_level_pos++;

    return 1;
}


int luaopen_libopvz_lua(lua_State *L)
{
	// lua_register(L, "hello", ihello);
  lua_register(L, "cube",  icube);
  lua_register(L, "sleep", sleep_c);
	return 0;
}
