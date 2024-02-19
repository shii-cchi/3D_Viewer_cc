#ifndef CPP4_3DVIEWER_MODEL_PARSER_H
#define CPP4_3DVIEWER_MODEL_PARSER_H

#include <fstream>
#include <map>
#include <vector>

namespace s21 {

struct DataFromFile {
  virtual void PushBack(double val) = 0;
  virtual ~DataFromFile() = default;
};

struct VertixCoordinates : public DataFromFile {
public:
  VertixCoordinates() : _x(0), _y(0), _z(0), _size(0) {}
  ~VertixCoordinates() override = default;
  double &operator[](size_t index);
  void PushBack(double val) override;
  double _x, _y, _z;

private:
  size_t _size;
};

struct SurfaceNumbers : public DataFromFile {
  unsigned int &operator[](size_t index) { return _surface_numbers[index]; }
  void PushBack(double val) override {
    unsigned int num = static_cast<unsigned int>(val);
    _surface_numbers.push_back(num);
  }
  ~SurfaceNumbers() override = default;
  std::vector<unsigned int> _surface_numbers;
};

struct CreateDataStructure {
  virtual DataFromFile *Create() = 0;
};

struct CreateVertix : public CreateDataStructure {
  DataFromFile *Create() override { return new VertixCoordinates(); }
};

struct CreateSurface : public CreateDataStructure {
  DataFromFile *Create() override { return new SurfaceNumbers(); }
};

class GeometryData final {
public:
  // Начинается с идекса 1
  GeometryData() : _amount_edges(0) {
    VertixCoordinates vertix;
    _data.first.push_back(vertix);
  };

  auto GetData() const { return _data; }

  void PushBack(VertixCoordinates *coord) { _data.first.push_back(*coord); };
  void PushBack(SurfaceNumbers *num) { _data.second.push_back(*num); };

private:
  std::pair<std::vector<VertixCoordinates>, std::vector<SurfaceNumbers>> _data;
  unsigned int _amount_edges;
};

class Parser final {
public:
  std::pair<std::vector<VertixCoordinates>, std::vector<SurfaceNumbers>>
  ParseFile(std::ifstream &file);
};

} // namespace s21

#endif // CPP4_3DVIEWER_MODEL_PARSER_H