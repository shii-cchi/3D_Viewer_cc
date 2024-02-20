#ifndef SRC_VIEW_GLVIEW_H
#define SRC_VIEW_GLVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../viewer_controller/viewer_controller.h"

class GlView : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit GlView(QWidget *parent = nullptr);

  void sendData(std::vector<s21::VertixCoordinates> all_vertices, std::vector<s21::SurfaceNumbers> all_surfaces, unsigned int amount_surfaces);
  void setupOpenGLState();

 public slots:
  void updateProjectionType(int index);
  void updateWidthEdge(int index);
  void updateLineType(int index);
  void updateSizeVertices(int index);
  void updateVerticesType(int index);

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  std::vector<s21::VertixCoordinates> all_vertices;
  std::vector<s21::SurfaceNumbers> all_surfaces;
  unsigned int count_surfaces;
  bool data_initialized;

  GLushort line_pattern;
  enum projection_types {
      Central,
      Parallel,
  };
  projection_types projection_type;

  float width_edge;
  float size_vertices;
  enum vertices_types {
        Default,
        Circular,
        Square
    };
  vertices_types vertices_type;

  void setupProjection();
  void drawObjects();
};

#endif  // SRC_VIEW_GLVIEW_H
