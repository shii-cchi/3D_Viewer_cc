#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QCloseEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QColorDialog>
#include <QSettings>

#include "../viewer_controller/viewer_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void projectionTypeChanged(int index);
  void widthEdgeChanged(int index);
  void lineTypeChanged(int index);
  void sizeVerticesChanged(int index);
  void verticesTypeChanged(int index);
  void colorChanged(int param, const QColor &color);

 private slots:
  void on_pushButton_file_clicked();
  void on_pushButton_move_clicked();
  void on_pushButton_rotate_clicked();
  void on_pushButton_scale_clicked();

  void on_projection_type_currentIndexChanged(int index);
  void on_width_edge_currentIndexChanged(int index);
  void on_line_type_currentIndexChanged(int index);
  void on_size_vertices_currentIndexChanged(int index);
  void on_vertices_type_currentIndexChanged(int index);

  void openColorDialogEdges();
  void openColorDialogVertices();
  void openColorDialogBackground();
  void colorSelected(const QColor &color);

  private:
  Ui::MainWindow *ui;
  std::vector<s21::VertixCoordinates> vertices;
  std::vector<s21::SurfaceNumbers> surfaces;
  unsigned int amount_surfaces;
  unsigned int amount_edges;

  void setDefaultSettings();
  QString getFileName(QString file_name);
  bool checkFile();
  bool isAngles(double degree_x, double degree_y, double degree_z);

  s21::ViewerController controller;

  QColorDialog colorDialog;
  int currentParam;
  QColor edges_color;
  QColor vertices_color;
  QColor background_color;

  QSettings settings;
  void loadSettings();
  void saveSettings();
};
#endif  // SRC_VIEW_MAINWINDOW_H
