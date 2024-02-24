#include "viewer_controller.h"

namespace s21 {

void ViewerController::SetRotate(double val) {
  _transform = new Rotate(val);
  _transform->SetModel(&_model);
}

void ViewerController::SetTranslate(double val) {
  _transform = new Translate(val);
  _transform->SetModel(&_model);
}

void ViewerController::SetScale(double val) {
  _transform = new Scale(val);
  _transform->SetModel(&_model);
}

void ViewerController::RotateForwardX(double val) {
  SetRotate(val);
  _transform->ExecuteX();
  delete _transform;
}

void ViewerController::RotateForwardY(double val) {
  SetRotate(val);
  _transform->ExecuteY();
  delete _transform;
}

void ViewerController::RotateForwardZ(double val) {
  SetRotate(val);
  _transform->ExecuteZ();
  delete _transform;
}

void ViewerController::TranslateForwardX(double val) {
  SetTranslate(val);
  _transform->ExecuteX();
  delete _transform;
}

void ViewerController::TranslateForwardY(double val) {
  SetTranslate(val);
  _transform->ExecuteY();
  delete _transform;
}

void ViewerController::TranslateForwardZ(double val) {
  SetTranslate(val);
  _transform->ExecuteZ();
  delete _transform;
}

void ViewerController::ScaleForward(double val) {
  SetScale(val);
  _transform->ExecuteX();
  _transform->ExecuteY();
  _transform->ExecuteZ();
  delete _transform;
}

}  // namespace s21