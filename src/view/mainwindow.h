#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QCloseEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

extern "C" {
#include "../core/parser.h"
#include "../core/transform.h"
}

#include "../core/structs.h"

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

  private:
  Ui::MainWindow *ui;
  obj_data data;

  void setDefaultSettings();
  void clearData();
  void closeEvent(QCloseEvent *event) override;
  QString getFileName(QString file_name);
  bool checkFile();
  bool isAngles(double degree_x, double degree_y, double degree_z);

  QSettings settings;
  void loadSettings();
  void saveSettings();
};
#endif  // SRC_VIEW_MAINWINDOW_H
