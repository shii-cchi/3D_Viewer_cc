#include "glview.h"

GlView::GlView(QWidget *parent) : QOpenGLWidget(parent), data_initialized(false), line_pattern(0xFFFF), projection_type(GL_PROJECTION_CENTRAL), width_edge(1), size_vertices(1) {}

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
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void GlView::paintGL() {
    if (data_initialized) {
        setupProjection();
        drawObjects();
    }
}

void GlView::setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (projection_type == GL_PROJECTION_PARALLEL) {
      glOrtho(-1, 1, -1, 1, 1, 99999);
    } else if (projection_type == GL_PROJECTION_CENTRAL) {
      glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 99999);
      glTranslatef(0, 0, -2.8);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GlView::drawObjects() {
    glLineWidth(width_edge);
    glPointSize(size_vertices);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, line_pattern);

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
    
    glDisable(GL_LINE_STIPPLE);
}

void GlView::updateProjectionType(int index) {
    switch (index) {
        case 0:
            projection_type = GL_PROJECTION_CENTRAL;
            break;
        case 1:
            projection_type = GL_PROJECTION_PARALLEL;
            break;
    }

    update();
}

void GlView::updateWidthEdge(int index) {
    switch (index) {
        case 0:
            width_edge = 1;
            break;
        case 1:
            width_edge = 2;
            break;
        case 2:
            width_edge = 3;
            break;
        case 3:
            width_edge = 0.8;
            break;
        case 4:
            width_edge = 0.5;
            break;
        case 5:
            width_edge = 0.2;
            break;
    }

    update();
}

void GlView::updateLineType(int index) {
    switch (index) {
        case 0:
            line_pattern = 0xFFFF;
            break;
        case 1:
            line_pattern = 0xF0F0;
            break;
    }

    update();
}

void GlView::updateSizeVertices(int index) {
    switch (index) {
        case 0:
            size_vertices = 1;
            break;
        case 1:
            size_vertices = 2;
            break;
        case 2:
            size_vertices = 3;
            break;
        case 3:
            size_vertices = 0.8;
            break;
        case 4:
            size_vertices = 0.5;
            break;
        case 5:
            size_vertices = 0.2;
            break;
    }

    update();
}

void GlView::updateVerticesType(int index) {

}