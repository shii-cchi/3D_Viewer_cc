#include "glview.h"

GlView::GlView(QWidget *parent)
    : QOpenGLWidget(parent),
      data_initialized(false),
      renderingSettings{0xFFFF, RenderingSettings::ProjectionType::kCentral,
                        1.0f, 1.0f, RenderingSettings::VerticesType::kDefault},
      colorSettings{
          ColorSettings::kEdgesColor, {0, 0, 0}, {255, 0, 0}, {255, 255, 255}} {}

void GlView::sendData(std::vector<s21::VertixCoordinates> vertices,
                      std::vector<s21::SurfaceNumbers> surfaces,
                      unsigned int amount_surfaces) {
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
  glClearColor(colorSettings.background_color.redF(),
               colorSettings.background_color.greenF(),
               colorSettings.background_color.blueF(), 1.0f);
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

  if (renderingSettings.projection_type ==
      RenderingSettings::ProjectionType::kParallel) {
    glOrtho(-1, 1, -1, 1, -1, 99999);
  } else if (renderingSettings.projection_type ==
             RenderingSettings::ProjectionType::kCentral) {
    glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 99999);
    glTranslatef(0, 0, -2.8);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GlView::drawObjects() {
  glLineWidth(renderingSettings.width_edge);

  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, renderingSettings.line_pattern);

  for (int i = 0; i < count_surfaces; ++i) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < 3; ++j) {
      glColor3d(colorSettings.edges_color.redF(),
                colorSettings.edges_color.greenF(),
                colorSettings.edges_color.blueF());
      glVertex3d(all_vertices[all_surfaces[i][j]][0],
                 all_vertices[all_surfaces[i][j]][1],
                 all_vertices[all_surfaces[i][j]][2]);
    }
    glEnd();
  }

  glDisable(GL_LINE_STIPPLE);

  if (renderingSettings.vertices_type !=
      RenderingSettings::VerticesType::kDefault) {
    if (renderingSettings.vertices_type ==
        RenderingSettings::VerticesType::kCircular) {
      glEnable(GL_POINT_SMOOTH);
    }

    glPointSize(renderingSettings.size_vertices);
    for (int i = 0; i < count_surfaces; ++i) {
      glBegin(GL_POINTS);
      for (int j = 0; j < 3; ++j) {
        glColor3d(colorSettings.vertices_color.redF(),
                  colorSettings.vertices_color.greenF(),
                  colorSettings.vertices_color.blueF());
        glVertex3d(all_vertices[all_surfaces[i][j]][0],
                   all_vertices[all_surfaces[i][j]][1],
                   all_vertices[all_surfaces[i][j]][2]);
      }
      glEnd();
    }

    if (renderingSettings.vertices_type ==
        RenderingSettings::VerticesType::kCircular) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}

void GlView::updateProjectionType(int index) {
  switch (index) {
    case 0:
      renderingSettings.projection_type =
          RenderingSettings::ProjectionType::kCentral;
      break;
    case 1:
      renderingSettings.projection_type =
          RenderingSettings::ProjectionType::kParallel;
      break;
  }

  update();
}

void GlView::updateWidthEdge(int index) {
  switch (index) {
    case 0:
      renderingSettings.width_edge = 1;
      break;
    case 1:
      renderingSettings.width_edge = 2;
      break;
    case 2:
      renderingSettings.width_edge = 3;
      break;
    case 3:
      renderingSettings.width_edge = 4;
      break;
    case 4:
      renderingSettings.width_edge = 5;
      break;
  }

  update();
}

void GlView::updateLineType(int index) {
  switch (index) {
    case 0:
      renderingSettings.line_pattern = 0xFFFF;
      break;
    case 1:
      renderingSettings.line_pattern = 0xF0F0;
      break;
  }

  update();
}

void GlView::updateSizeVertices(int index) {
  switch (index) {
    case 0:
      renderingSettings.size_vertices = 1;
      break;
    case 1:
      renderingSettings.size_vertices = 2;
      break;
    case 2:
      renderingSettings.size_vertices = 3;
      break;
    case 3:
      renderingSettings.size_vertices = 4;
      break;
    case 4:
      renderingSettings.size_vertices = 5;
      break;
  }

  update();
}

void GlView::updateVerticesType(int index) {
  switch (index) {
    case 0:
      renderingSettings.vertices_type =
          RenderingSettings::VerticesType::kDefault;
      break;
    case 1:
      renderingSettings.vertices_type =
          RenderingSettings::VerticesType::kCircular;
      break;
    case 2:
      renderingSettings.vertices_type = RenderingSettings::VerticesType::kSquare;
      break;
  }

  update();
}

void GlView::onColorChanged(ColorSettings::CurrentParam param,
                            const QColor &color) {
  switch (param) {
    case ColorSettings::kEdgesColor:
      colorSettings.edges_color = color;
      break;
    case ColorSettings::kVerticesColor:
      colorSettings.vertices_color = color;
      break;
    case ColorSettings::kBackgroundColor:
      colorSettings.background_color = color;
      break;
  }

  update();
}
