#ifndef SRC_VIEW_COLORSETTINGS_H
#define SRC_VIEW_COLORSETTINGS_H

#include <QColor>

struct ColorSettings {
  enum CurrentParam {
    EdgesColor,
    VerticesColor,
    BackgroundColor
  };

  CurrentParam current_param;
  QColor edges_color;
  QColor vertices_color;
  QColor background_color;
};

#endif // SRC_VIEW_COLORSETTINGS_H
