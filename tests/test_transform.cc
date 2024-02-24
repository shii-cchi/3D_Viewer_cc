#include "test.h"

TEST(TransformTest, Rotate) {
    s21::ViewerController controller;
    std::string path = "../tests/test_2.obj";
    std::vector<std::vector<double>> coord;
    coord.push_back({0.433296, 1.235728, 0.116508});
    coord.push_back({0.433296, 1.235728, 0.116509});
    coord.push_back({-1.116802, 0.441995, -0.534545});
    coord.push_back({ -1.116802, 0.441995, -0.534545});
    coord.push_back({-0.433296, -1.235728, -0.116509});
    coord.push_back({-0.433296, -1.235728, -0.116508});
    coord.push_back({1.116802, -0.441995, 0.534545});
    coord.push_back({1.116802, -0.441995, 0.534545});
    controller.SetDataNotCentered(path);
    controller.RotateForwardX(57.2958);
    controller.RotateForwardY(114.5916);
    controller.RotateForwardZ(171.8874);
    std::vector<s21::VertixCoordinates> vec;
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i - 1][j], vec[i][j]);
        }
    }
}

TEST(TransformTest, Scale) {
    s21::ViewerController controller;
    std::string path = "../tests/test_1.obj";
    std::vector<std::vector<double>> coord;
    coord.push_back({-0.100000, -0.100000, 0.100000});
    coord.push_back({0.100000, -0.100000, 0.100000});
    coord.push_back({-0.100000, 0.100000, 0.100000});
    coord.push_back({0.100000, 0.100000, 0.100000});
    coord.push_back({-0.100000, 0.100000, -0.100000});
    coord.push_back({0.100000, 0.100000, -0.100000});
    coord.push_back({-0.100000, -0.100000, -0.100000});
    coord.push_back({0.100000, -0.100000, -0.100000});
    controller.SetDataNotCentered(path);
    controller.ScaleForward(0.1);
    std::vector<s21::VertixCoordinates> vec;
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i - 1][j], vec[i][j]);
        }
    }
}

TEST(TransformTest, Translate) {
    s21::ViewerController controller;
    std::string path = "../tests/test_1.obj";
    std::vector<std::vector<double>> coord;
    coord.push_back({-0.5 + 0.5, -0.5 + 0.6, 0.5 + 0.7});
    coord.push_back({0.5 + 0.5, -0.5 + 0.6, 0.5 + 0.7});
    coord.push_back({-0.5 + 0.5, 0.5 + 0.6, 0.5 + 0.7});
    coord.push_back({0.5 + 0.5, 0.5 + 0.6, 0.5 + 0.7});
    coord.push_back({-0.5 + 0.5, 0.5 + 0.6, -0.5 + 0.7});
    coord.push_back({0.5 + 0.5, 0.5 + 0.6, -0.5 + 0.7});
    coord.push_back({-0.5 + 0.5, -0.5 + 0.6, -0.5 + 0.7});
    coord.push_back({0.5 + 0.5, -0.5 + 0.6, -0.5 + 0.7});
    controller.SetDataNotCentered(path);
    controller.TranslateForwardX(0.5);
    controller.TranslateForwardY(0.6);
    controller.TranslateForwardZ(0.7);
    std::vector<s21::VertixCoordinates> vec;
    for(size_t i = 1; i < vec.size(); i++) {
        for(int j = 0; j < 3; j++) {
            EXPECT_EQ(coord[i - 1][j], vec[i][j]);
        }
    }
}

