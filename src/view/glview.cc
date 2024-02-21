#include "glview.h"

GlView::GlView(QWidget *parent) : QOpenGLWidget(parent), data_initialized(false), line_pattern(0xFFFF), projection_type(Central), width_edge(1), size_vertices(1), vertices_type(Default), edges_color(0, 0, 0), vertices_color(255, 0, 0), background_color(255, 255, 255)  {}

void GlView::sendData(std::vector<s21::VertixCoordinates> vertices, std::vector<s21::SurfaceNumbers> surfaces, unsigned int amount_surfaces) {
  all_vertices = vertices;
  all_surfaces = surfaces;
  count_surfaces = amount_surfaces;
  data_initialized = true;
}

void GlView::initializeGL() {
  initializeOpenGLFunctions();
  setupOpenGLState();
}

void GlView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GlView::setupOpenGLState() {
    glClearColor(background_color.redF(), background_color.greenF(), background_color.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void GlView::paintGL() {
    if (data_initialized) {
        setupOpenGLState();
        setupProjection();
        glEnableClientState(GL_VERTEX_ARRAY);
        drawObjects();
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void GlView::setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (projection_type == Parallel) {
      glOrtho(-1, 1, -1, 1, -1, 99999);
    } else if (projection_type == Central) {
      glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 99999);
      glTranslatef(0, 0, -2.8);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GlView::drawObjects() {
    glLineWidth(width_edge);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, line_pattern);

    for (int i = 0; i < count_surfaces; ++i) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < 3; ++j) {
        glColor3d(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
        glVertex3d(all_vertices[all_surfaces[i][j]][0],
                   all_vertices[all_surfaces[i][j]][1],
                   all_vertices[all_surfaces[i][j]][2]);
      }
      glEnd();
    }

    glDisable(GL_LINE_STIPPLE);

    if (vertices_type != Default) {
      if (vertices_type == Circular) {
        glEnable(GL_POINT_SMOOTH);
      }

      glPointSize(size_vertices);
      for (int i = 0; i < count_surfaces; ++i) {
        glBegin(GL_POINTS);
        for (int j = 0; j < 3; ++j) {
            glColor3d(vertices_color.redF(), vertices_color.greenF(), vertices_color.blueF());
            glVertex3d(all_vertices[all_surfaces[i][j]][0],
                   all_vertices[all_surfaces[i][j]][1],
                   all_vertices[all_surfaces[i][j]][2]);
        }
        glEnd();
      }

      if (vertices_type == Circular) {
        glDisable(GL_POINT_SMOOTH);
      }
    }
}

void GlView::updateProjectionType(int index) {
    switch (index) {
        case 0:
            projection_type = Central;
            break;
        case 1:
            projection_type = Parallel;
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
            width_edge = 4;
            break;
        case 4:
            width_edge = 5;
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
            size_vertices = 4;
            break;
        case 4:
            size_vertices = 5;
            break;
    }

    update();
}

void GlView::updateVerticesType(int index) {
    switch (index) {
        case 0:
            vertices_type = Default;
            break;
        case 1:
            vertices_type = Circular;
            break;
        case 2:
            vertices_type = Square;
            break;
    }

    update();
}

void GlView::onColorChanged(int param, const QColor &color) {
    switch (param) {
        case 0:
            edges_color = color;
            break;
        case 1:
            vertices_color = color;
            break;
        case 2:
            background_color = color;
            break;
    }

    update();
}
