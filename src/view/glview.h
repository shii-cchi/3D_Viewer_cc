#ifndef SRC_VIEW_GLVIEW_H
#define SRC_VIEW_GLVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../core/structs.h"

class GlView : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit GlView(QWidget *parent = nullptr);
  
  void sendData(obj_data file_data);
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

  obj_data data;
  bool data_initialized;
  GLushort line_pattern;
  GLenum projection_type;
  float width_edge;
  float size_vertices;
  enum vertex_shape {
        Default,
        Circular,
        Square
    };
    vertex_shape vertex_type;

  void setupProjection();
  void drawObjects();
};

#endif  // SRC_VIEW_GLVIEW_H
