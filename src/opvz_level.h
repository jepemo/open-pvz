/**
 *
 */
#ifndef __OPVZ_LEVEL_H__
#define __OPVZ_LEVEL_H__

#define MAX_ENTITIES 512

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
  short *depth;
  /* Game objects in the level */
  short *entities;
} Level;

LevelConfig * level_config_new(size_t rows, size_t cols, short depth);

Level * level_new        (LevelConfig *config);
Level * level_new_default(void);

#endif /* __OPVZ_LEVEL_H__ */
