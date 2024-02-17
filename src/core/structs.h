#ifndef SRC_CORE_STRUCTS_H
#define SRC_CORE_STRUCTS_H

typedef struct {
  double x;
  double y;
  double z;
} vertices;

typedef struct {
  unsigned int *indices;
  int amount_of_vertices;
} surfaces;

typedef struct {
  vertices *all_vertices;
  surfaces *all_surfaces;
  int count_vertices;
  int count_surfaces;
} obj_data;

#endif  // SRC_CORE_STRUCTS_H
