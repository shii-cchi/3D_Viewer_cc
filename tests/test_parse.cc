#include "test.h"

TEST(Parse_test, Vertices) {
    s21::ViewerController controller;
    std::vector<std::vector<double>> coord;
    coord.push_back({-0.5, -0.5, 0.5});
    coord.push_back({0.5, -0.5, 0.5});
    coord.push_back({-0.5, 0.5, 0.5});
    coord.push_back({0.5, 0.5, 0.5});
    coord.push_back({-0.5, 0.5, -0.5});
    coord.push_back({0.5, 0.5, -0.5});
    coord.push_back({-0.5, -0.5, -0.5});
    coord.push_back({0.5, -0.5, -0.5});
    std::string path = "../tests/test_1.obj";
    controller.SetDataNotCentered(path);
    std::vector<s21::VertixCoordinates> vec =
        controller.GetVetrixCoordinate();
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i - 1][j], vec[i][j]);
        }
    }
    coord.clear();
    controller.Clear();
    path = "../tests/test_2.obj";
    controller.SetDataNotCentered(path);
    coord.push_back({3.0119111, -3.5, 3.765026});
    coord.push_back({3.01191, -3.5, 3.765026});
    coord.push_back({3.0119111, 3.5, 3.765026});
    coord.push_back({3.01191, 3.5, 3.765026});
    coord.push_back({3.0119111, 3.5, -3.234974});
    coord.push_back({3.01191, 3.5, -3.234974});
    coord.push_back({3.0119111, -3.5, -3.234974});
    coord.push_back({3.01191, -3.5, -3.234974});
    vec = controller.GetVetrixCoordinate();
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i - 1][j], vec[i][j]);
        }
    }
}

TEST(Parse_test, Surfaces) {
    s21::ViewerController controller;
    std::vector<std::vector<double>> coord;
    coord.push_back({1, 2, 3});
    coord.push_back({3, 2, 4});
    coord.push_back({3, 4, 5});
    coord.push_back({5, 4, 6});
    coord.push_back({5, 6, 7});
    coord.push_back({7, 6, 8});
    coord.push_back({7, 8, 1});
    coord.push_back({1, 8, 2});
    coord.push_back({2, 8, 4});
    coord.push_back({4, 8, 6});
    coord.push_back({7, 1, 5});
    coord.push_back({5, 1, 3});
    std::string path = "../tests/test_1.obj";
    controller.SetDataNotCentered(path);
    std::vector<s21::SurfaceNumbers> vec =
        controller.GetSurfaceNum();
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i][j], vec[i][j]);
        }
    }
    controller.Clear();
    controller.SetDataNotCentered(path);
    path = "../tests/test_2.obj";
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i][j], vec[i][j]);
        }
    }
}