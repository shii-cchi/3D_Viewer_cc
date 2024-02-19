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
  _size++;
  switch (_size) {
  case 1:
    _x = val;
    break;
  case 2:
    _y = val;
    break;
  case 3:
    _z = val;
    break;
  default:
    throw std::range_error("Vertex overflow!\n");
    break;
  }
}

std::pair<std::vector<VertixCoordinates>, std::vector<SurfaceNumbers>>
Parser::ParseFile(std::ifstream &file) {
  GeometryData data;
  DataFromFile *data_file;
  CreateSurface creator_surf;
  CreateVertix creator_vert;
  CreateDataStructure *creators[] = {&creator_surf, &creator_vert};
  std::map<char, unsigned int> type = {{'v', 0}, {'f', 1}};
  std::string line;
  auto push_data = [](std::string &buffer, DataFromFile *data_file) {
    data_file->PushBack(std::stod(buffer));
    buffer.clear();
  };
  auto parse_line = [&line, &push_data](DataFromFile *data_file) {
    std::string buffer;
    unsigned int pos = 0;
    while (line[pos] != '\r') {
      pos = (line.find(" ", pos) < line.find("\r", pos))
                ? line.find(" ", pos) + 1
                : line.find("\r", pos);
      while (std::isdigit(line[pos]) || line[pos] == '.' || line[pos] == '-') {
        buffer.push_back(line[pos]);
        pos++;
      }
      if (!(buffer.empty()))
        push_data(buffer, data_file);
    }
    pos = 0;
  };

  while (std::getline(file, line)) {
    if (type.count(line[0])) {
      switch (type[line[0]]) {
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