#include "parser.h"

namespace s21 {

double &VertixCoordinates::operator[](size_t index) {
  switch (index) {
  case 0:
    return _x;
    break;
  case 1:
    return _y;
    break;
  case 2:
    return _z;
    break;
  default:
    throw std::range_error("Index must be less than 3!\n");
    break;
  }
  return _z;
}

void VertixCoordinates::PushBack(double val) {
  auto max_min_coord = [&](double &max_val, double &min_val, double val) {
    min_val = (val < min_val) ? val : min_val;
    max_val = (val > max_val) ? val : max_val;
  };
  auto max_min_coord_first = [&](double &max_val, double &min_val, double val) {
    max_val = (_amount_vert == 2) ? val : max_val;
    min_val = (_amount_vert == 2) ? val : min_val;
  };
  _size++;
  switch (_size) {
  case 1:
    max_min_coord(_max_coord_x, _min_coord_x, val);
    _x = val;
    break;
  case 2:
    max_min_coord(_max_coord_y, _min_coord_y, val);
    _y = val;
    break;
  case 3:
    max_min_coord(_max_coord_z, _min_coord_z, val);
    _z = val;
    break;
  default:
    throw std::range_error("Vertex overflow!\n");
    break;
  }
  max_min_coord_first(_max_coord_x, _min_coord_x, _x);
  max_min_coord_first(_max_coord_y, _min_coord_y, _y);
  max_min_coord_first(_max_coord_z, _min_coord_z, _z);
}

void SurfaceNumbers::PushBack(double val) {
  unsigned int num = static_cast<unsigned int>(val);
  _surface_numbers.push_back(num);
  if (_surface_numbers.size() > 1) {
    for (size_t i = 0; i < _surface_numbers.size() - 1; i++) {
      _all_edges.insert(std::set{
          _surface_numbers[i], _surface_numbers[_surface_numbers.size() - 1]});
    }
  }
}

std::pair<std::vector<VertixCoordinates>, std::vector<SurfaceNumbers>>
Parser::ParseFile(std::ifstream &file) {
  GeometryData data;
  DataFromFile *data_file;
  CreateSurface creator_surf;
  CreateVertix creator_vert;
  CreateDataStructure *creators[] = {&creator_surf, &creator_vert};
  std::map<std::string, unsigned int> type = {{"v ", 0}, {"f ", 1}};
  std::string line;
  auto push_data = [](std::string &buffer, DataFromFile *data_file) {
    data_file->PushBack(std::stod(buffer));
    buffer.clear();
  };
  auto parse_line = [&line, &push_data](DataFromFile *data_file) {
    std::string buffer;
    unsigned int pos = 0;
    while (pos < line.size() && line[pos] != '\r') {
      pos = (line.find(" ", pos) < line.find("\r", pos))
                ? line.find(" ", pos) + 1
                : line.find("\r", pos);
      while (
          pos < line.size() && pos != std::string::npos &&
          (std::isdigit(line[pos]) || line[pos] == '.' || line[pos] == '-')) {
        buffer.push_back(line[pos]);
        pos++;
      }
      if (!(buffer.empty()))
        push_data(buffer, data_file);
    }
    pos = 0;
  };

  while (std::getline(file, line)) {
    std::string type_coord(std::string(line.begin(), line.begin() + 2));
    if (type.count(type_coord)) {
      switch (type[type_coord]) {
      case 0:
        data_file = creators[1]->Create();
        parse_line(data_file);
        data.PushBack(dynamic_cast<VertixCoordinates *>(data_file));
        break;
      case 1:
        data_file = creators[0]->Create();
        parse_line(data_file);
        data.PushBack(dynamic_cast<SurfaceNumbers *>(data_file));
        break;
      }
      delete data_file;
    }
  }
  return data.GetData();
}

} // namespace s21