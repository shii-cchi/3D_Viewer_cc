#include "parser.h"

void get_file_data(char *file_name, obj_data *data) {
  FILE *obj_file = open_file_func(file_name);
  if (obj_file != NULL) {
    count_ver_and_faces(obj_file, data);
    fclose(obj_file);
    data->all_vertices = allocate_memory_vert(data->count_vertices);
    data->all_surfaces = allocate_memory_surf(data->count_surfaces);
    filling_ver_and_faces(data, file_name);
    centering(data);
  }
}

void count_ver_and_faces(FILE *obj_file, obj_data *data) {
  char str_in_file[256] = "abc";
  data->count_surfaces = 0;
  data->count_vertices = 0;
  while (fgets(str_in_file, 255, obj_file)) {
    data->count_vertices = (str_in_file[0] == 'v' && str_in_file[1] == ' ')
                               ? data->count_vertices + 1
                               : data->count_vertices;
    data->count_surfaces = (str_in_file[0] == 'f' && str_in_file[1] == ' ')
                               ? data->count_surfaces + 1
                               : data->count_surfaces;
  }
}

FILE *open_file_func(char *file_name) {
  FILE *obj_file = fopen(file_name, "r");
  return obj_file;
}

void filling_ver_and_faces(obj_data *data, char *file_name) {
  FILE *obj_file = open_file_func(file_name);
  char str_in_file[256] = "abc";
  int len = 0;
  int i_vert = 0, i_surf = 0;
  while (fgets(str_in_file, 255, obj_file)) {
    if (str_in_file[0] == 'v' && str_in_file[1] == ' ') {
      filling_v(str_in_file, data->all_vertices, i_vert);
      i_vert++;
    } else if (str_in_file[0] == 'f' && str_in_file[1] == ' ') {
      len = strlen(str_in_file);
      filling_f(str_in_file, data->all_surfaces, i_surf, len);
      i_surf++;
    }
  }
  fclose(obj_file);
}

void filling_v(char *str_in_file, vertices *vert, int i) {
  char array_of_numbers[3][256] = {"0", "0", "0"};
  int j_str = (str_in_file[2] != ' ') ? 0 : 1;
  int i_number = 0, j_arr = 0;
  while (str_in_file[2 + j_str] != '\n') {
    if (i_number < 3) {
      filling_str(str_in_file, array_of_numbers[i_number], &i_number, &j_str,
                  &j_arr);
      j_arr++;
    }
    j_str++;
  }
  array_of_numbers[i_number][j_arr] = '\0';
  vert[i].x = convertValue(array_of_numbers[0]);
  vert[i].y = convertValue(array_of_numbers[1]);
  vert[i].z = convertValue(array_of_numbers[2]);
}

void filling_f(char *str_in_file, surfaces *surf, int i, int len) {
  str_in_file[len] = '\n';
  int space_flag = 1;
  int count_ind = 0;
  int i_number = 0, j_str = 0, j_arr = 0;
  surf[i].amount_of_vertices = count_amount_of_vert(str_in_file);
  surf[i].indices =
      (unsigned int *)calloc(surf[i].amount_of_vertices, sizeof(unsigned int));
  int dim = surf[i].amount_of_vertices;
  char array_of_numbers[dim][256];
  while (str_in_file[2 + j_str] != '\n' && str_in_file[2 + j_str] != '\0' &&
         str_in_file[2 + j_str] != '\r') {
    check_space(str_in_file[2 + j_str], &space_flag);
    if (space_flag) {
      filling_str(str_in_file, array_of_numbers[i_number], &i_number, &j_str,
                  &j_arr);
      j_arr++;
    }
    j_str++;
  }
  array_of_numbers[i_number][j_arr] = '\0';
  while (count_ind < surf[i].amount_of_vertices) {
    surf[i].indices[count_ind] =
        (int)convertValue(array_of_numbers[count_ind]) - 1;
    count_ind++;
  }
}

void check_space(char ch, int *space_flag) {
  if (ch == '/') {
    *space_flag = 0;
  } else if (ch == ' ') {
    *space_flag = 1;
  }
}

void filling_str(char *str_in_file, char *array_of_numbers, int *i_number,
                 int *j_str, int *j_arr) {
  if (str_in_file[2 + *j_str] == ' ') {
    array_of_numbers[*j_arr] = '\0';
    *i_number = *i_number + 1;
    *j_arr = -1;
  } else {
    if (checkNumbers(str_in_file[2 + *j_str])) {
      array_of_numbers[*j_arr] = str_in_file[2 + *j_str];
    }
  }
}

int count_amount_of_vert(char *str_in_file) {
  int numbers = 0, j_str = 0;
  while (str_in_file[j_str] != '\n') {
    if (str_in_file[j_str] == ' ' && checkNumbers(str_in_file[j_str + 1]))
      numbers++;
    j_str++;
  }
  return numbers;
}

vertices *allocate_memory_vert(int amount_vert) {
  vertices *all_vert = (vertices *)calloc(amount_vert, sizeof(vertices));
  return all_vert;
}

surfaces *allocate_memory_surf(int amount_surf) {
  surfaces *all_surf = (surfaces *)calloc(amount_surf, sizeof(surfaces));
  return all_surf;
}

int countPoint(char *number) {
  int i = 0;
  int point = 0;
  int flag_minus = 0;
  while (number[i] != '\0') {
    if (number[i] == '-') {
      flag_minus = 1;
    }
    if (number[i] == '.') {
      point = i - 1;
      break;
    }
    i++;
  }
  if (point == 0) {
    point = i - 1;
  }
  if (flag_minus) {
    point -= 1;
  }
  return point;
}

double convertValue(char *number) {
  int deg = countPoint(number);
  int min_flag = 0;
  int i = 0;
  double res = 0;
  while (number[i] != '\0') {
    if (number[i] != '.' && number[i] != '-') {
      res += pow(10, deg) * ((int)number[i] - 48);
      deg--;
    }
    if (number[i] == '-') {
      min_flag = 1;
    }
    i++;
  }
  return res * pow(-1, min_flag);
}

void centering(obj_data *data) {
  double max_x = 0, max_y = 0, max_z = 0;
  double min_x = 0, min_y = 0, min_z = 0;
  max_coord(data, &max_x, &max_y, &max_z);
  min_coord(data, &min_x, &min_y, &min_z);
  double delta_x = max_x / 2 + min_x / 2;
  double delta_y = max_y / 2 + min_y / 2;
  double delta_z = max_z / 2 + min_z / 2;
  double values[6] = {max_x, max_y, max_z, min_x, min_y, min_z};
  double max_val = max_val_func(values);
  centering_func(data, delta_x, delta_y, delta_z);
  rescale_func(data, max_val);
}

void max_coord(obj_data *data, double *max_x, double *max_y, double *max_z) {
  *max_x = data->all_vertices[0].x;
  *max_y = data->all_vertices[0].y;
  *max_z = data->all_vertices[0].z;
  for (int i = 0; i < data->count_vertices; i++) {
    *max_x =
        (data->all_vertices[i].x > *max_x) ? data->all_vertices[i].x : *max_x;
    *max_y =
        (data->all_vertices[i].y > *max_y) ? data->all_vertices[i].y : *max_y;
    *max_z =
        (data->all_vertices[i].z > *max_z) ? data->all_vertices[i].z : *max_z;
  }
}

void min_coord(obj_data *data, double *min_x, double *min_y, double *min_z) {
  *min_x = data->all_vertices[0].x;
  *min_y = data->all_vertices[0].y;
  *min_z = data->all_vertices[0].z;
  for (int i = 0; i < data->count_vertices; i++) {
    *min_x =
        (data->all_vertices[i].x < *min_x) ? data->all_vertices[i].x : *min_x;
    *min_y =
        (data->all_vertices[i].y < *min_y) ? data->all_vertices[i].y : *min_y;
    *min_z =
        (data->all_vertices[i].z < *min_z) ? data->all_vertices[i].z : *min_z;
  }
}

void centering_func(obj_data *data, double delta_x, double delta_y,
                    double delta_z) {
  for (int i = 0; i < data->count_vertices; i++) {
    data->all_vertices[i].x -= delta_x;
    data->all_vertices[i].y -= delta_y;
    data->all_vertices[i].z -= delta_z;
  }
}

double max_val_func(double *values) {
  double max = values[0];
  for (int i = 0; i < 6; i++) {
    max = (fabs(max) < fabs(values[i])) ? values[i] : max;
  }
  return max;
}

void rescale_func(obj_data *data, double max_val) {
  int deg = (max_val < 0) ? 1 : 0;
  for (int i = 0; i < data->count_vertices; i++) {
    data->all_vertices[i].x *= (double)1 / max_val * pow(-1, deg);
    data->all_vertices[i].y *= (double)1 / max_val * pow(-1, deg);
    data->all_vertices[i].z *= (double)1 / max_val * pow(-1, deg);
  }
}

int checkNumbers(char symbol) {
  return ((int)symbol > 44 && (int)symbol < 58 && (int)symbol != 47);
}

void clear_memory(obj_data *data) {
  for (int i = 0; i < data->count_surfaces; i++) {
    free(data->all_surfaces[i].indices);
  }
  free(data->all_surfaces);
  free(data->all_vertices);
}