# open-pvz
Tower Defense Game Engine inspired by "Plantz Vz Zombiez", implemented in C with differents bindings for other languages.

- [Getting Started](#getting-started)
- [Example](#example)
- [Bindings](#bindings)

## Getting Started

### Build & Install

In **Linux** (Ubuntu)

Install compiler and lua headers

```bash
apt-get install gcc
```
In **Mac OS**
Install [brew](https://brew.sh/)

Install lua:

```bash
brew install lua

```

**Get** the sourcecode:
```
git clone https://github.com/jepemo/open-pvz.git
```

**Build** library, executing the make command:
```
cd open-pvz
make
```

## Example

### C Simple level example

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

  bool finished = false;
  while(!finished) {
    level_print_debug(level);

    LevelStatus * status = level_step(level);
    finished = status->finished;
  }

  level_destroy(level);

  return 0;
}
```

### Output:

![C Program animation](doc/c_anim.gif)


## Bindings:
 * Lua ([Documentation](doc/lua.md))
 * Java (Todo)
