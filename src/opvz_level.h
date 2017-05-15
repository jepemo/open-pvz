/**
 *
 *
 */

#ifndef __OPEN_PVZ_H__
#define __OPEN_PVZ_H__

typedef struct {
  int n_rows;
  int n_cols;
  short **depth;
} Level;

Level * level_new (void);

#endif /* __OPEN_PVZ_H__ */
