#include "viewer_model.h"

namespace s21 {

void ViewerModel::ParseFile(std::string &path) {
  std::ifstream file;
  file.open(path);
  if (file.is_open()) {
    auto [vertices_coord, surfaces_num] = _parser.ParseFile(file);
    file.close();
    _scaler.Centering(vertices_coord);
    _scaler.Rescale(vertices_coord);
    _vertices_coord = vertices_coord;
    _surface_num = surfaces_num;
  } else {
    throw std::invalid_argument("Incorrect path of file!\n");
  }
};

void ViewerModel::RotateX(double val) {
  RotateStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyX(_vertices_coord);
}

void ViewerModel::RotateY(double val) {
  RotateStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyY(_vertices_coord);
}

void ViewerModel::RotateZ(double val) {
  RotateStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyZ(_vertices_coord);
}

void ViewerModel::TranslateX(double val) {
  TranslateStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyX(_vertices_coord);
}

void ViewerModel::TranslateY(double val) {
  TranslateStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyY(_vertices_coord);
}

void ViewerModel::TranslateZ(double val) {
  TranslateStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyZ(_vertices_coord);
}

void ViewerModel::ScaleX(double val) {
  ScaleStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyX(_vertices_coord);
}

void ViewerModel::ScaleY(double val) {
  ScaleStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyY(_vertices_coord);
}

void ViewerModel::ScaleZ(double val) {
  ScaleStrategy strategy(val);
  _transformer.SetStrategy(&strategy);
  _transformer.UseStrategyZ(_vertices_coord);
}

} // namespace s21