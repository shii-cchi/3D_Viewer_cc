#ifndef CPP4_3DVIEWER_MODEL_MODEL_H
#define CPP4_3DVIEWER_MODEL_MODEL_H

#include <stdexcept>
#include <string>
#include <vector>

#include "transform.h"

namespace s21 {

class ViewerModel final {
public:
  auto GetVertices() const { return _vertices_coord; }
  auto GetSurfaces() const { return _surface_num; }

  void RotateX(double val);
  void RotateY(double val);
  void RotateZ(double val);

  void TranslateX(double val);
  void TranslateY(double val);
  void TranslateZ(double val);

  void ScaleX(double val);
  void ScaleY(double val);
  void ScaleZ(double val);

  void ParseFile(std::string &path);

private:
  std::vector<VertixCoordinates> _vertices_coord;
  std::vector<SurfaceNumbers> _surface_num;

  Parser _parser;
  Transformer _transformer;
};

} // namespace s21

#endif // CPP4_3DVIEWER_MODEL_MODEL_H