#ifndef SRC_CORE_TRANSFORM_H
#define SRC_CORE_TRANSFORM_H

#define M_PI 3.14159265358979323846
#include <math.h>

#include "structs.h"

void move_coord(double shift_x, double shift_y, double shift_z, obj_data *data);

void scale(double ratio, obj_data *data);

void rotate(double degree_x, double degree_y, double degree_z, obj_data *data);
void rotate_x(obj_data *data, double degree_x);
void rotate_y(obj_data *data, double degree_y);
void rotate_z(obj_data *data, double degree_z);
double convert_to_rad(double degree);

#endif  // SRC_CORE_TRANSFORM_H
