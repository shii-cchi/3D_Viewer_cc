#ifndef SRC_VIEW_GLVIEW_H
#define SRC_VIEW_GLVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../viewer_controller/viewer_controller.h"
#include "colorsettings.h"

class GlView : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit GlView(QWidget *parent = nullptr);

  void sendData(std::vector<s21::VertixCoordinates> all_vertices,
                std::vector<s21::SurfaceNumbers> all_surfaces,
                unsigned int amount_surfaces);
  void setupOpenGLState();

 public slots:
  void updateProjectionType(int index);
  void updateWidthEdge(int index);
  void updateLineType(int index);
  void updateSizeVertices(int index);
  void updateVerticesType(int index);
  void onColorChanged(ColorSettings::CurrentParam param, const QColor &color);

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  std::vector<s21::VertixCoordinates> all_vertices;
  std::vector<s21::SurfaceNumbers> all_surfaces;
  unsigned int count_surfaces;
  bool data_initialized;

  struct RenderingSettings {
    GLushort line_pattern;

    enum ProjectionType {
      Central,
      Parallel,
    };
    ProjectionType projection_type;

    float width_edge;
    float size_vertices;

    enum VerticesType { Default, Circular, Square };
    VerticesType vertices_type;
  };

  RenderingSettings renderingSettings;
  ColorSettings colorSettings;

  void setupProjection();
  void drawObjects();
};

#endif  // SRC_VIEW_GLVIEW_H
