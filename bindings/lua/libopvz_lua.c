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

/*
static int sleep_c(lua_State *L){
	long secs = lua_tointeger(L, -1);
	sleep(secs);
	return 0;
}

static int icube(lua_State *L){
	float rtrn = lua_tonumber(L, -1);
	lua_pushnumber(L,rtrn*rtrn*rtrn);
	return 1;
}
*/


static int ilevel_new(lua_State *L)
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

static int ilevel_destroy(lua_State *L)
{
	int level_ident = lua_tonumber(L, -1);
	Level * level = global_levels[level_ident];
	level_destroy(level);
	global_levels[level_ident] = NULL;

	return 0;
}

static int ilevel_step(lua_State *L)
{
	int level_ident = lua_tonumber(L, -1);

	Level * level = global_levels[level_ident];
	level_step(level);

	return 0;
}

static int ilevel_add_plant(lua_State *L)
{
	int y      = lua_tonumber(L, -1);
	int x      = lua_tonumber(L, -2);
	int hit    = lua_tonumber(L, -3);
	int health = lua_tonumber(L, -4);
	int type   = lua_tonumber(L, -5);
	int lvl_id = lua_tonumber(L, -6);

	Entity * new_plant = plant_new(type, health, hit);
	Level  * level     = global_levels[lvl_id];

	level_add_entity(level, new_plant, x, y);

	return 0;
}

static int ilevel_add_zombie(lua_State *L)
{
	int y      = lua_tonumber(L, -1);
	int x      = lua_tonumber(L, -2);
	int speed  = lua_tonumber(L, -3);
	int hit    = lua_tonumber(L, -4);
	int health = lua_tonumber(L, -5);
	int type   = lua_tonumber(L, -6);
	int lvl_id = lua_tonumber(L, -7);

	Entity * new_z = zombie_new(type, health, hit, speed);
	Level  * level     = global_levels[lvl_id];

	level_add_entity(level, new_z, x, y);

	return 0;
}

int luaopen_libopvz_lua(lua_State *L)
{
	lua_register(L, "level_new", ilevel_new);
	lua_register(L, "level_destroy", ilevel_destroy);
	lua_register(L, "level_step", ilevel_step);
	lua_register(L, "level_add_plant", ilevel_add_plant);
	lua_register(L, "level_add_zombie", ilevel_add_zombie);
	return 0;
}
