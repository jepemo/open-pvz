/**
 *
 *
 */

#ifndef __OPEN_PVZ_H__
#define __OPEN_PVZ_H__

typedef struct {
  /* Number of map rows */
  size_t n_rows;
  /* Number of map cols */
  size_t n_cols;
  /* Default value to init depth */
  short init_depth;
} LevelConfig;

typedef struct {
  /* Level configuration*/
  LevelConfig *config;
  /* Surface profundity. Default is 0 */
  short **depth;
  /* Game objects in the level */
  short ***level_objects;
} Level;

LevelConfig * level_config_new(size_t rows, size_t cols, short depth);

Level * level_new        (LevelConfig *config);
Level * level_new_default(void);

int hello(int i);

#endif /* __OPEN_PVZ_H__ */
