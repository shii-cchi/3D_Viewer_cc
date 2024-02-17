#include "glview.h"

GlView::GlView(QWidget *parent) : QOpenGLWidget(parent), data_initialized(false) {}

void GlView::sendData(obj_data file_data) {
  data = file_data;
  data_initialized = true;
}

void GlView::initializeGL() {
  initializeOpenGLFunctions();
  setupOpenGLState();
}

void GlView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GlView::setupOpenGLState() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void GlView::paintGL() {
    if (dataInitialized) {
        setupProjection();
        drawObjects();
    }
}

void GlView::setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 99999);
    glTranslatef(0, 0, -2.8);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GlView::drawObjects() {
    for (int i = 0; i < data.count_surfaces; ++i) {
      for (int j = 0; j < data.all_surfaces[i].amount_of_vertices; ++j) {
        glBegin(GL_LINE_LOOP);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(data.all_vertices[data.all_surfaces[i].indices[j]].x,
                   data.all_vertices[data.all_surfaces[i].indices[j]].y,
                   data.all_vertices[data.all_surfaces[i].indices[j]].z);
      }
      glEnd();
    }
}