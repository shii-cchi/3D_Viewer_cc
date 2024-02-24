#ifndef CPP4_3DVIEWER_VIEWER_MODEL_PARSER_H
#define CPP4_3DVIEWER_VIEWER_MODEL_PARSER_H

#include <fstream>
#include <map>
#include <set>
#include <vector>

namespace s21 {

class DataFromFile {
 public:
  virtual void PushBack(double val) = 0;
  virtual size_t Size() const = 0;
  virtual ~DataFromFile() = default;
};

class VertixCoordinates : public DataFromFile {
 public:
  VertixCoordinates() : _x(0), _y(0), _z(0), _size(0) { _amount_vert++; }
  ~VertixCoordinates() override = default;

  static double GetMaxX() { return _max_coord_x; }
  static double GetMaxY() { return _max_coord_y; }
  static double GetMaxZ() { return _max_coord_z; }
  static double GetMinX() { return _min_coord_x; }
  static double GetMinY() { return _min_coord_y; }
  static double GetMinZ() { return _min_coord_z; }
  static void SetMaxX(double val) { _max_coord_x = val; }
  static void SetMaxY(double val) { _max_coord_y = val; }
  static void SetMaxZ(double val) { _max_coord_z = val; }
  static void SetMinX(double val) { _min_coord_x = val; }
  static void SetMinY(double val) { _min_coord_y = val; }
  static void SetMinZ(double val) { _min_coord_z = val; }
  size_t Size() const override { return _size; };

  double &operator[](size_t index);
  void PushBack(double val) override;
  static void Clear() {
    _max_coord_x = 0;
    _max_coord_y = 0;
    _max_coord_z = 0;
    _min_coord_x = 0;
    _min_coord_y = 0;
    _min_coord_z = 0;
  }

 private:
  static inline double _max_coord_x{};
  static inline double _max_coord_y{};
  static inline double _max_coord_z{};
  static inline double _min_coord_x{};
  static inline double _min_coord_y{};
  static inline double _min_coord_z{};
  static inline double _amount_vert{};
  double _x, _y, _z;
  size_t _size;
};

class SurfaceNumbers : public DataFromFile {
 public:
  SurfaceNumbers() { _amount_surfaces++; }
  ~SurfaceNumbers() override = default;

  unsigned int &operator[](size_t index) { return _surface_numbers[index]; }
  void PushBack(double val) override;
  static void Clear() {
    _amount_surfaces = 0;
    _all_edges.clear();
  };

  static auto GetAmountSurfaces() { return _amount_surfaces; }
  static auto GetAmountEdges() { return _all_edges.size(); }
  size_t Size() const override { return _surface_numbers.size(); }

 private:
  static inline unsigned int _amount_surfaces{};
  static inline std::set<std::set<unsigned int>> _all_edges;
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
  GeometryData() {
    VertixCoordinates vertix;
    _data.first.push_back(vertix);
  };

  auto GetData() const { return _data; }

  void PushBack(VertixCoordinates *coord) { _data.first.push_back(*coord); };
  void PushBack(SurfaceNumbers *num) { _data.second.push_back(*num); };

 private:
  std::pair<std::vector<VertixCoordinates>, std::vector<SurfaceNumbers>> _data;
};

class Parser final {
 public:
  std::pair<std::vector<VertixCoordinates>, std::vector<SurfaceNumbers>>
  ParseFile(std::ifstream &file);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_VIEWER_MODEL_PARSER_H