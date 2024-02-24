#include "test.h"

TEST(Amount_tests, AmountSurf) {
    s21::ViewerController controller;
    std::string path = "../tests/test_1.obj";
    controller.SetData(path);
    EXPECT_EQ(controller.GetAmountSurfaces(), 12);
    controller.Clear();
    path.clear();
    path = "../tests/test_2.obj";
    controller.SetData(path);
    EXPECT_EQ(controller.GetAmountSurfaces(), 12);
}

TEST(Amount_tests, AmountEdges) {
    s21::ViewerController controller;
    std::string path = "../tests/test_2.obj";
    controller.SetData(path);
    EXPECT_EQ(controller.GetAmountEdges(), 18);
    controller.Clear();
    path.clear();
    path = "../tests/test_2.obj";
    controller.SetData(path);
    EXPECT_EQ(controller.GetAmountEdges(), 18);
}
