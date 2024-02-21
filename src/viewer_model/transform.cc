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
    coord[0] = coord[0] * cos(_val) + coord[2] * sin(_val);
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

void Scaler::Centering(std::vector<VertixCoordinates> &coordinates) {
  double delta_x =
      VertixCoordinates::GetMaxX() / 2 + VertixCoordinates::GetMinX() / 2;

  double delta_y =
      VertixCoordinates::GetMaxY() / 2 + VertixCoordinates::GetMinY() / 2;

  double delta_z =
      VertixCoordinates::GetMaxZ() / 2 + VertixCoordinates::GetMinZ() / 2;

  std::array<double, 3> delta = {delta_x, delta_y, delta_z};
  for (auto &vec : coordinates) {
    for (size_t i = 0; i < vec.Size(); i++) {
      vec[i] -= delta[i];
    }
  }
  _centered_coord = coordinates;
}

void Scaler::Rescale(std::vector<VertixCoordinates> &coordinates) {
  double max_x =
      (fabs(VertixCoordinates::GetMaxX()) > fabs(VertixCoordinates::GetMinX()))
          ? VertixCoordinates::GetMaxX()
          : VertixCoordinates::GetMinX();

  double max_y =
      (fabs(VertixCoordinates::GetMaxY()) > fabs(VertixCoordinates::GetMinY()))
          ? VertixCoordinates::GetMaxY()
          : VertixCoordinates::GetMinY();

  double max_z =
      (fabs(VertixCoordinates::GetMaxZ()) > fabs(VertixCoordinates::GetMinZ()))
          ? VertixCoordinates::GetMaxZ()
          : VertixCoordinates::GetMinZ();

  std::array<double, 3> max_values = {max_x, max_y, max_z};
  double max_val = *std::max_element(max_values.begin(), max_values.end());
  unsigned int deg = (max_val > 0) ? 0 : 1;
  for (auto &vec : coordinates) {
    for (size_t i = 0; i < vec.Size(); i++) {
      vec[i] *= pow(-1, deg) / max_val;
    }
  }
}

} // namespace s21
