#ifndef CPP4_3DVIEWER_VIEWER_MODEL_MODEL_H
#define CPP4_3DVIEWER_VIEWER_MODEL_MODEL_H

#include <stdexcept>
#include <string>
#include <vector>

#include "transform.h"

namespace s21 {

class ViewerModel final {
 public:
  auto GetVertices() const { return _vertices_coord; }
  auto GetSurfaces() const { return _surface_num; }
  auto GetAmountSurfaces() const { return SurfaceNumbers::GetAmountSurfaces(); }
  auto GetAmountEdges() const { return SurfaceNumbers::GetAmountEdges(); }

  void RotateX(double val);
  void RotateY(double val);
  void RotateZ(double val);

  void TranslateX(double val);
  void TranslateY(double val);
  void TranslateZ(double val);

  void Centering() { _scaler.Centering(_vertices_coord); }

  void Rescale() { _scaler.Rescale(_vertices_coord); }

  void ScaleX(double val);
  void ScaleY(double val);
  void ScaleZ(double val);

  void ParseFile(std::string &path);
  void ParseFileNotCentered(std::string &path);
  void CenteringRescale(std::vector<VertixCoordinates> &coord) {
    _scaler.Centering(coord);
    _scaler.Rescale(coord);
  }

  void Clear() {
    VertixCoordinates::Clear();
    SurfaceNumbers::Clear();
    _vertices_coord.clear();
    _surface_num.clear();
  };

 private:
  std::vector<VertixCoordinates> _vertices_coord;
  std::vector<SurfaceNumbers> _surface_num;
  unsigned int _amount_surfaces;
  unsigned int _amount_edges;

  Parser _parser;
  Transformer _transformer;
  Scaler _scaler;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_VIEWER_MODEL_MODEL_H