#ifndef CPP4_3DVIEWER_CONTROLLER_CONTROLLER_H
#define CPP4_3DVIEWER_CONTROLLER_CONTROLLER_H
#define _USE_MATH_DEFINES

#include "../viewer_model/viewer_model.h"

namespace s21 {

class Transform {
public:
  virtual ~Transform() {}

  virtual void ExecuteX() = 0;
  virtual void ExecuteY() = 0;
  virtual void ExecuteZ() = 0;
  virtual void UnExecuteX() = 0;
  virtual void UnExecuteY() = 0;
  virtual void UnExecuteZ() = 0;

  void SetModel(ViewerModel *model) { _model = model; }

protected:
  ViewerModel *_model;
};

class Rotate final : public Transform {
public:
  Rotate(double grad) { _rad = grad / 180 * M_PI; };

  void ExecuteX() override { this->_model->RotateX(_rad); }
  void ExecuteY() override { this->_model->RotateY(_rad); }
  void ExecuteZ() override { this->_model->RotateZ(_rad); }
  void UnExecuteX() override { this->_model->RotateX(-_rad); }
  void UnExecuteY() override { this->_model->RotateY(-_rad); }
  void UnExecuteZ() override { this->_model->RotateZ(-_rad); }

private:
  double _rad;
};

class Translate final : public Transform {
public:
  Translate(double val) : _shift(val) {}

  void ExecuteX() override { this->_model->TranslateX(_shift); }
  void ExecuteY() override { this->_model->TranslateY(_shift); }
  void ExecuteZ() override { this->_model->TranslateZ(_shift); }
  void UnExecuteX() override { this->_model->TranslateX(_shift); }
  void UnExecuteY() override { this->_model->TranslateY(_shift); }
  void UnExecuteZ() override { this->_model->TranslateZ(_shift); }

private:
  double _shift;
};

class Scale final : public Transform {
public:
  Scale(double val) : _scale_factor(val) {}

  void ExecuteX() override { this->_model->ScaleX(_scale_factor); }
  void ExecuteY() override { this->_model->ScaleY(_scale_factor); }
  void ExecuteZ() override { this->_model->ScaleZ(_scale_factor); }
  void UnExecuteX() override { this->_model->ScaleX(1 / _scale_factor); }
  void UnExecuteY() override { this->_model->ScaleY(1 / _scale_factor); }
  void UnExecuteZ() override { this->_model->ScaleZ(1 / _scale_factor); }

private:
  double _scale_factor;
};

class ViewerController final {
public:
  void RotateForwardX(double rad);
  void RotateForwardY(double rad);
  void RotateForwardZ(double rad);
  void RotateBackX(double rad);
  void RotateBackY(double rad);
  void RotateBackZ(double rad);

  void TranslateForwardX(double val);
  void TranslateForwardY(double val);
  void TranslateForwardZ(double val);
  void TranslateBackX(double val);
  void TranslateBackY(double val);
  void TranslateBackZ(double val);

  void ScaleForward(double val);
  void ScaleBack(double val);

  void Centering() { _model.Centering(); }
  void Rescale() { _model.Rescale(); }

  void SetData(std::string &path) { _model.ParseFile(path); }

  auto GetVetrixCoordinate() const { return _model.GetVertices(); }
  auto GetSurfaceNum() const { return _model.GetSurfaces(); }
  auto GetAmountSurfaces() const { return _model.GetAmountSurfaces(); }
  auto GetAmountEdges() const { return _model.GetAmountEdges(); }

private:
  ViewerModel _model;
  Transform *_transform;

  void SetRotate(double val);
  void SetTranslate(double val);
  void SetScale(double val);
};

} // namespace s21

#endif // CPP4_3DVIEWER_CONTROLLER_CONTROLLER_H