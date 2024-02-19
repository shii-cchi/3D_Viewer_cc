#include "transform.h"

namespace s21 {

void RotateStrategy::TransformationX(std::vector<VertixCoordinates> &vec) {

  for (auto &coord : vec) {
    double tmp_y = coord[1];
    coord[1] = coord[1] * cos(_val) - coord[2] * sin(_val);
    coord[2] = tmp_y * sin(_val) + coord[2] * cos(_val);
  }
}

void RotateStrategy::TransformationY(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    double tmp_x = coord[0];
    coord[0] = coord[0] * cos(_val) + coord[3] * sin(_val);
    coord[2] = -tmp_x * sin(_val) + coord[2] * cos(_val);
  }
}

void RotateStrategy::TransformationZ(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    double tmp_x = coord[0];
    coord[0] = coord[0] * cos(_val) - coord[1] * sin(_val);
    coord[1] = tmp_x * sin(_val) + coord[1] * cos(_val);
  }
}

void TranslateStrategy::TransformationX(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    coord[0] = coord[0] + _val;
  }
}

void TranslateStrategy::TransformationY(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    coord[1] = coord[1] + _val;
  }
}

void TranslateStrategy::TransformationZ(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    coord[2] = coord[2] + _val;
  }
}

void ScaleStrategy::TransformationX(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    coord[0] = coord[0] * _val;
  }
}

void ScaleStrategy::TransformationY(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    coord[1] = coord[1] * _val;
  }
}

void ScaleStrategy::TransformationZ(std::vector<VertixCoordinates> &vec) {
  for (auto &coord : vec) {
    coord[2] = coord[2] * _val;
  }
}

} // namespace s21