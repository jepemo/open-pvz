# open-pvz
Tower Defense Game Engine inspired by "Plantz Vz Zombiez", implemented in C with differents bindings for other languages.

- [Getting Started](#getting-started)
- [Example](#example)
- [Bindings](#bindings)

## Getting Started

### Install

#### Linux (Ubuntu)

Install compiler and lua headers

```bash
apt-get install gcc
```
#### Mac OS
Install [brew](https://brew.sh/)

Install lua:

```bash
brew install lua
```

## Example

```c
#include "opvz.h"

void level_init (Level *level)
{
  // plants
  level_add_entity(level, PLANT_SUNFLOWER, 0, 0);
  level_add_entity(level, PLANT_SUNFLOWER, 0, 1);
  level_add_entity(level, PLANT_SUNFLOWER, 0, 2);
  level_add_entity(level, PLANT_SUNFLOWER, 0, 3);
  level_add_entity(level, PLANT_SUNFLOWER, 0, 4);

  level_add_entity(level, PLANT_PEASHOOTER, 1, 0);
  level_add_entity(level, PLANT_PEASHOOTER, 1, 1);
  level_add_entity(level, PLANT_PEASHOOTER, 1, 2);
  level_add_entity(level, PLANT_PEASHOOTER, 1, 3);
  level_add_entity(level, PLANT_PEASHOOTER, 1, 4);

  // Zombies
  level_add_entity(level, ZOMBIE_REGULAR, 8, 0);
  level_add_entity(level, ZOMBIE_REGULAR, 8, 1);
  level_add_entity(level, ZOMBIE_REGULAR, 8, 2);
  level_add_entity(level, ZOMBIE_REGULAR, 8, 3);
  level_add_entity(level, ZOMBIE_REGULAR, 8, 4);
}

int main (int argc, char **argv)
{
  Level *level = level_new_default();

  level_init(level);

  int finished = 0;
  while((finished = level_finished(level)) == 0) {
    level_print_debug(level);
    level = level_step(level);
  }

  level_destroy(level);

  if      (finished == -1) print("Zombies WON!\n");
  else if (finished == 1) printf("Plants WON!\n")

  return 0;
}
```

## Bindings:
 * Lua ([Documentation](doc/lua.md))
 * Java (Todo)
