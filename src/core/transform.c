#include "transform.h"

void rotate(double degree_x, double degree_y, double degree_z, obj_data *data) {
  rotate_x(data, degree_x);
  rotate_y(data, degree_y);
  rotate_z(data, degree_z);
}

void rotate_x(obj_data *data, double degree_x) {
  double degree_x_rad = convert_to_rad(degree_x);
  double val_1 = 0, val_2 = 0;
  for (int i = 0; i < data->count_vertices; i++) {
    val_1 = data->all_vertices[i].y;
    val_2 = data->all_vertices[i].z;
    data->all_vertices[i].y =
        val_1 * cos(degree_x_rad) - val_2 * sin(degree_x_rad);
    data->all_vertices[i].z =
        val_1 * sin(degree_x_rad) + val_2 * cos(degree_x_rad);
  }
}

void rotate_y(obj_data *data, double degree_y) {
  double degree_y_rad = convert_to_rad(degree_y);
  double val_1 = 0, val_2 = 0;
  for (int i = 0; i < data->count_vertices; i++) {
    val_1 = data->all_vertices[i].x;
    val_2 = data->all_vertices[i].z;
    data->all_vertices[i].x =
        val_1 * cos(degree_y_rad) + val_2 * sin(degree_y_rad);
    data->all_vertices[i].z =
        -val_1 * sin(degree_y_rad) + val_2 * cos(degree_y_rad);
  }
}

void rotate_z(obj_data *data, double degree_z) {
  double degree_z_rad = convert_to_rad(degree_z);
  double val_1 = 0, val_2 = 0;
  for (int i = 0; i < data->count_vertices; i++) {
    val_1 = data->all_vertices[i].x;
    val_2 = data->all_vertices[i].y;
    data->all_vertices[i].x =
        val_1 * cos(degree_z_rad) - val_2 * sin(degree_z_rad);
    data->all_vertices[i].y =
        val_1 * sin(degree_z_rad) + val_2 * cos(degree_z_rad);
  }
}

double convert_to_rad(double degree) {
  double deg = (degree / (double)360) * 2 * M_PI;
  return deg;
}

void scale(double ratio, obj_data *data) {
  for (int i = 0; i < data->count_vertices; i++) {
    data->all_vertices[i].x *= ratio;
    data->all_vertices[i].y *= ratio;
    data->all_vertices[i].z *= ratio;
  }
}

void move_coord(double shift_x, double shift_y, double shift_z,
                obj_data *data) {
  for (int i = 0; i < data->count_vertices; i++) {
    data->all_vertices[i].x += shift_x;
    data->all_vertices[i].y += shift_y;
    data->all_vertices[i].z += shift_z;
  }
}