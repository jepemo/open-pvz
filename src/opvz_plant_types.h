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
#ifndef __OPVZ_PLANT_H__
#define __OPVZ_PLANT_H__

#include "opvz_plant.h"
                                   /* type,  health, armor, hit */
#define PLANT_SUNFLOWER  plant_new(    0,      5,     5,     0)
#define PLANT_PEASHOOTER plant_new(    1,      5,     5,     1)
#define PLANT_CHERRYBOMB plant_new(    2,      999,   999,   60)
#define PLANT_WALLNUT    plant_new(    3,      15,    50,    0)

#endif /* __OPVZ_PLANT_H__ */