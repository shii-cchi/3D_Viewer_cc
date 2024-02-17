#ifndef SRC_CORE_PARSER_H
#define SRC_CORE_PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

#define VERTICES 100

void get_file_data(char *file_name, obj_data *data);

void filling_ver_and_faces(obj_data *data, char *file_name);
void filling_v(char *str_in_file, vertices *vert, int i);
void filling_f(char *str_in_file, surfaces *surf, int i, int len);
void filling_str(char *str_in_file, char *array_of_numbers, int *i_number,
                 int *j_str, int *j_arr);
void check_space(char ch, int *space_flag);
int count_amount_of_vert(char *str_in_file);
int countPoint(char *number);
double convertValue(char *number);
void count_ver_and_faces(FILE *obj_file, obj_data *data);
FILE *open_file_func(char *file_name);
vertices *allocate_memory_vert(int amount_ver);
surfaces *allocate_memory_surf(int amount_surf);
void centering(obj_data *data);
void max_coord(obj_data *data, double *max_x, double *max_y, double *max_z);
void min_coord(obj_data *data, double *min_x, double *min_y, double *min_z);
void centering_func(obj_data *data, double delta_x, double delta_y,
                    double delta_z);
double max_val_func(double *values);
void rescale_func(obj_data *data, double max_val);
int checkNumbers(char symbol);
void clear_memory(obj_data *data);

#endif  // SRC_CORE_PARSER_H
