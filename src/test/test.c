#include <check.h>

#include "../core/structs.h"
#include "../core/parser.h"
#include "../core/transform.h"

obj_data data;

START_TEST(amount_of_vert) {
  get_file_data("test/test_1.obj", &data);
  ck_assert_int_eq(8, data.count_vertices);
  clear_memory(&data);
}
END_TEST

START_TEST(amount_of_surf) {
  get_file_data("test/test_1.obj", &data);
  ck_assert_int_eq(12, data.count_surfaces);
  clear_memory(&data);
}
END_TEST

START_TEST(values_vert) {
  char file_name[] = "test/test_1.obj";
  double Values[22] = {-1,   -1, 1,  1,  -1,
                  1, -1, 1,  1,  1,
                  1, 1,  -1, 1,  -1,
                  1, 1,  -1, -1, -1,
                  -1};
  get_file_data(file_name, &data);
  int j = 1;
  for (int i = 1; i < data.count_vertices - 2; i++) {
    if(i%3 == 1) {
        ck_assert_double_eq(Values[i - 1], data.all_vertices[j - 1].x);
    } else if(i%3 == 2) {
        ck_assert_double_eq(Values[i - 1], data.all_vertices[j - 1].y);
    } else {
        ck_assert_double_eq(Values[i - 1], data.all_vertices[j - 1].z);
    }
    j = (i%3 == 0) ? j + 1 : j;
  }
   clear_memory(&data);
}
END_TEST

START_TEST(values_surf) {
  char file_name[] = "test/test_1.obj";
  int values[36] = {0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 
               3, 5, 4, 5, 6, 6, 5, 7, 6, 7, 0, 0, 
               7, 1, 1, 7, 3, 3, 7, 5, 6, 0, 4, 4, 
               0, 2};
  get_file_data(file_name, &data);
  int j = -1;
  for (int i = 0; i < data.count_surfaces; i++) {
    j = ((i)%3 == 0) ? j + 1 : j;
    ck_assert_int_eq(values[i], data.all_surfaces[j].indices[(i)%3]);
  }
  clear_memory(&data);
}
END_TEST

START_TEST(rotates) {
  char file_name[] = "test/test_2.obj";
  double val[24] = {  0.433296,  1.235728,  0.116508,
 0.433296,  1.235728,  0.116509,
 -1.116802,  0.441995,  -0.534545,
 -1.116802,  0.441995,  -0.534545,
 -0.433296,  -1.235728,  -0.116509,
 -0.433296,  -1.235728,  -0.116508,
 1.116802,  -0.441995,  0.534545,
 1.116802,  -0.441995,  0.534545};
  get_file_data(file_name, &data);
  rotate(57.2958, 114.5916, 171.8874, &data);
  int j = 1;
  for (int i = 1; i < data.count_vertices; i++) {
    if(i%3 == 1) {
       ck_assert_double_eq_tol(val[i - 1], data.all_vertices[j - 1].x, 1e-6);
    } else if(i%3 == 2) {
        ck_assert_double_eq_tol(val[i - 1], data.all_vertices[j - 1].y, 1e-6);
    } else {
        ck_assert_double_eq_tol(val[i - 1], data.all_vertices[j - 1].z, 1e-6);
    }
    j = (i%3 == 0) ? j + 1 : j;
  }
  clear_memory(&data);
}
END_TEST

START_TEST(scales) {
  char file_name[] = "test/test_1.obj";
  double val[24] = {-0.100000, -0.100000, 0.100000,
0.100000, -0.100000, 0.100000,
-0.100000, 0.100000, 0.100000,
0.100000, 0.100000, 0.100000,
-0.100000, 0.100000, -0.100000,
0.100000, 0.100000, -0.100000,
-0.100000, -0.100000, -0.100000,
0.100000, -0.100000, -0.100000};
  get_file_data(file_name, &data);
  scale(0.1, &data);
  int j = 1;
  for (int i = 1; i < data.count_vertices; i++) {
    if(i%3 == 1) {
       ck_assert_double_eq_tol(val[i - 1], data.all_vertices[j - 1].x, 1e-6);
    } else if(i%3 == 2) {
        ck_assert_double_eq_tol(val[i - 1], data.all_vertices[j - 1].y, 1e-6);
    } else {
        ck_assert_double_eq_tol(val[i - 1], data.all_vertices[j - 1].z, 1e-6);
    }
    j = (i%3 == 0) ? j + 1 : j;
  }
  clear_memory(&data);
}
END_TEST

START_TEST(move_tests) {
  char file_name[] = "test/test_1.obj";
  double Values[22] = {-1 + 0.5,   -1 + 0.6, 1 + 0.7,  1 + 0.5,  -1 + 0.6,
                  1 + 0.7, -1 + 0.5, 1 + 0.6,  1 + 0.7,  1 + 0.5,
                  1 + 0.6, 1 + 0.7,  -1 + 0.5, 1 + 0.6,  -1 + 0.7,
                  1 + 0.5, 1 + 0.6,  -1 + 0.7, -1 + 0.5, -1 + 0.6,
                  -1 + 0.7};
  get_file_data(file_name, &data);
  move_coord(0.5, 0.6, 0.7, &data);
  int j = 1;
  for (int i = 1; i < data.count_vertices - 2; i++) {
    if(i%3 == 1) {
        ck_assert_double_eq(Values[i - 1], data.all_vertices[j - 1].x);
    } else if(i%3 == 2) {
        ck_assert_double_eq(Values[i - 1], data.all_vertices[j - 1].y);
    } else {
        ck_assert_double_eq(Values[i - 1], data.all_vertices[j - 1].z);
    }
    j = (i%3 == 0) ? j + 1 : j;
  }
   clear_memory(&data);
}
END_TEST

Suite *viewer_suite() {
  Suite *suite = suite_create("3d_viewer");
  TCase *tcase_core = tcase_create("3d_viewer");
  tcase_add_test(tcase_core, amount_of_vert);
  tcase_add_test(tcase_core, amount_of_surf);
  tcase_add_test(tcase_core, values_vert);
  tcase_add_test(tcase_core, values_surf);
  tcase_add_test(tcase_core, rotates);
  tcase_add_test(tcase_core, scales);
  tcase_add_test(tcase_core, move_tests);
  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main() {
  Suite *suite = viewer_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  srunner_free(suite_runner);
  return 0;
}
