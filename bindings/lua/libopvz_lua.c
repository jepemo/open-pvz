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


static int icreate_new_level(lua_State *L)
{
	// (int rows, int cols, int depth)
	int rows = lua_tonumber(L, -3);
	int cols = lua_tonumber(L, -2);
	// int deph = lua_tonumber(L, -1);
	int depth = 0;

	LevelConfig * config = level_config_new(rows, cols, depth);
	Level * new_level = level_new(config);

	global_levels[current_level_pos] = new_level;

	lua_pushnumber(L, current_level_pos);

	current_level_pos++;

	return 1;
}

static int ilevel_step(lua_State *L)
{
	int level_ident = lua_tonumber(L, -1);

	Level * level = global_levels[level_ident];
	level_step(level);

	return 0;
}

int luaopen_libopvz_lua(lua_State *L)
{
	lua_register(L, "create_new_level", icreate_new_level);
	lua_register(L, "level_step", ilevel_step);
	return 0;
}
