#ifndef CPP4_3DVIEWER_MODEL_TRANSFORM_H
#define CPP4_3DVIEWER_MODEL_TRANSFORM_H

#include <cmath>

#include "parser.h"

namespace s21 {

class TransformStrategy {
public:
  TransformStrategy(double val) : _val(val) {}
  virtual ~TransformStrategy() {}
  virtual void TransformationX(std::vector<VertixCoordinates> &vec) = 0;
  virtual void TransformationY(std::vector<VertixCoordinates> &vec) = 0;
  virtual void TransformationZ(std::vector<VertixCoordinates> &vec) = 0;

protected:
  double _val;
};

class RotateStrategy final : public TransformStrategy {
public:
  RotateStrategy(double val) : TransformStrategy(val) {}

  void TransformationX(std::vector<VertixCoordinates> &vec) override;
  void TransformationY(std::vector<VertixCoordinates> &vec) override;
  void TransformationZ(std::vector<VertixCoordinates> &vec) override;
};

class TranslateStrategy final : public TransformStrategy {
public:
  TranslateStrategy(double val) : TransformStrategy(val) {}

  void TransformationY(std::vector<VertixCoordinates> &vec) override;
  void TransformationZ(std::vector<VertixCoordinates> &vec) override;
  void TransformationX(std::vector<VertixCoordinates> &vec) override;
};

class ScaleStrategy final : public TransformStrategy {
public:
  ScaleStrategy(double val) : TransformStrategy(val) {}

  void TransformationX(std::vector<VertixCoordinates> &vec) override;
  void TransformationY(std::vector<VertixCoordinates> &vec) override;
  void TransformationZ(std::vector<VertixCoordinates> &vec) override;
};

class Transformer {
public:
  void SetStrategy(TransformStrategy *strategy) { _strategy = strategy; }
  void UseStrategyX(std::vector<VertixCoordinates> &vec) {
    _strategy->TransformationX(vec);
  };

  void UseStrategyY(std::vector<VertixCoordinates> &vec) {
    _strategy->TransformationY(vec);
  };

  void UseStrategyZ(std::vector<VertixCoordinates> &vec) {
    _strategy->TransformationZ(vec);
  };

private:
  TransformStrategy *_strategy;
};

} // namespace s21

#endif // CPP4_3DVIEWER_MODEL_TRANSFORM_H