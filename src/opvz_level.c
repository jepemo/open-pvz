#include <stdlib.h>
#include <string.h>
#include "opvz_level.h"


LevelConfig *
level_config_new(size_t rows, size_t cols, short depth)
{
  LevelConfig *config = malloc(sizeof(LevelConfig));
  config->n_rows = rows;
  config->n_cols = cols;
  config->init_depth = depth;

  return config;
}

Level *
level_new (LevelConfig *config)
{
  Level *level = malloc(sizeof(Level));

  level->config = config;

  short dimension = (level->config->n_rows * level->config->n_cols);

  level->depth = malloc(dimension * sizeof(short));
  memset(level->depth, 0, dimension);

  return level;
}

/**
 * Create a map of 5x9, with depth 0
 */
Level *
level_new_default(void)
{
  LevelConfig * config = level_config_new(5, 9, 0);
  return level_new(config);
}
