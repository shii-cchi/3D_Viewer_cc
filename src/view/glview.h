#ifndef SRC_VIEW_GLVIEW_H
#define SRC_VIEW_GLVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../core/structs.h"

class GlView : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit GlView(QWidget *parent = nullptr);

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  obj_data data;
  bool data_initialized;

  void sendData(obj_data file_data);
  void setupOpenGLState();
  void setupProjection();
  void drawObjects();
};

#endif  // SRC_VIEW_GLVIEW_H
