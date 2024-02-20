#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("3D_Viewer");

  connect(this, SIGNAL(projectionTypeChanged(int)), ui->view_window, SLOT(updateProjectionType(int)));
  connect(this, SIGNAL(widthEdgeChanged(int)), ui->view_window, SLOT(updateWidthEdge(int)));
  connect(this, SIGNAL(lineTypeChanged(int)), ui->view_window, SLOT(updateLineType(int)));
  connect(this, SIGNAL(sizeVerticesChanged(int)), ui->view_window, SLOT(updateSizeVertices(int)));
  connect(this, SIGNAL(verticesTypeChanged(int)), ui->view_window, SLOT(updateVerticesType(int)));

  loadSettings();
}

MainWindow::~MainWindow() { 
  saveSettings();
  delete ui; 
}

void MainWindow::saveSettings() {
    QSettings settings("s21", "3D_Viewer");

    settings.setValue("line_pattern", ui->line_type->currentIndex());
    settings.setValue("projection_type", ui->projection_type->currentIndex());
    settings.setValue("width_edge", ui->width_edge->currentIndex());
    settings.setValue("size_vertices", ui->size_vertices->currentIndex());
    settings.setValue("vertices_type", ui->vertices_type->currentIndex());
}

void MainWindow::loadSettings() {
    QSettings settings("s21", "3D_Viewer");

    int line_pattern_index = settings.value("line_pattern", 0).toInt();
    ui->line_type->setCurrentIndex(line_pattern_index);

    int projection_type_index = settings.value("projection_type", 0).toInt();
    ui->projection_type->setCurrentIndex(projection_type_index);

    int width_edge_index = settings.value("width_edge", 0).toInt();
    ui->width_edge->setCurrentIndex(width_edge_index);

    int size_vertices_index = settings.value("size_vertices", 0).toInt();
    ui->size_vertices->setCurrentIndex(size_vertices_index);

    int vertices_type_index = settings.value("vertices_type", 0).toInt();
    ui->vertices_type->setCurrentIndex(vertices_type_index);
}

void MainWindow::on_pushButton_file_clicked() {
  setDefaultSettings();

  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/", tr("Files (*.obj)"));

  if (file_name != "") {
   // clearData();

    std::string file_name_string = file_name.toStdString();
    controller.SetData(file_name_string);

    ui->file_name->setText(getFileName(file_name));

    // ui->count_vertices->setText(QString::number(data.count_vertices));
    // ui->count_surfaces->setText(QString::number(data.count_surfaces));

    vertices = controller.GetVetrixCoordinate();
    surfaces = controller.GetSurfaceNum();

    ui->view_window->sendData(vertices, surfaces);
    ui->view_window->update();

    // if (data.count_vertices != 0 && data.count_surfaces != 0) {
    //   ui->view_window->sendData(data);
    //   ui->view_window->update();
    // } else if (data.count_vertices == 0 && data.count_surfaces == 0) {
    //   ui->error_file->setText("Файл пустой");
    // } else {
    //   ui->error_file->setText("Недостаточно данных");
    // }
  } else {
    ui->error_file->setText("Откройте файл");
  }
}

void MainWindow::setDefaultSettings() {
  ui->error_file->setText("");
  ui->error_xyz_scale->setText("");
  ui->file_name->setText("");
  ui->count_vertices->setText("");
  ui->count_surfaces->setText("");
  ui->x_move->setText("0");
  ui->y_move->setText("0");
  ui->z_move->setText("0");
  ui->x_rotate->setText("0");
  ui->y_rotate->setText("0");
  ui->z_rotate->setText("0");
  ui->scale->setText("1");

  ui->view_window->setupOpenGLState();
}

// void MainWindow::clearData() {
//   if (data.all_vertices != nullptr) {
//     free(data.all_vertices);
//     data.all_vertices = nullptr;
//   }

//   if (data.all_surfaces != nullptr) {
//     for (int i = 0; i < data.count_surfaces; i++) {
//       free(data.all_surfaces[i].indices);
//     }
//     free(data.all_surfaces);
//     data.all_surfaces = nullptr;
//   }

//   data.count_vertices = 0;
//   data.count_surfaces = 0;
// }

void MainWindow::closeEvent(QCloseEvent *event) {
  //clearData();
  event->accept();
}

QString MainWindow::getFileName(QString file_name) {
  QStringList splited_str = file_name.split("/");
  file_name = splited_str.last();
  return file_name;
}

void MainWindow::on_pushButton_move_clicked() {
 ui->error_xyz_scale->setText("");

 //if (checkFile()) {
   bool x_err, y_err, z_err;
   double shift_x = ui->x_move->text().toDouble(&x_err);
   double shift_y = ui->y_move->text().toDouble(&y_err);
   double shift_z = ui->z_move->text().toDouble(&z_err);

   if (x_err && y_err && z_err) {
    controller.TranslateForwardX(shift_x);
    controller.TranslateForwardY(shift_y);
    controller.TranslateForwardZ(shift_z);

    vertices = controller.GetVetrixCoordinate();
    surfaces = controller.GetSurfaceNum();

   } else {
     ui->error_xyz_scale->setText("Неверно введенные данные");
   }
   ui->view_window->update();
 //}
}

void MainWindow::on_pushButton_rotate_clicked() {
 ui->error_xyz_scale->setText("");

 //if (checkFile()) {
   bool x_err, y_err, z_err;
   double degree_x = ui->x_rotate->text().toDouble(&x_err);
   double degree_y = ui->y_rotate->text().toDouble(&y_err);
   double degree_z = ui->z_rotate->text().toDouble(&z_err);

   if (x_err && y_err && z_err && isAngles(degree_x, degree_y, degree_z)) {
    controller.RotateForwardX(degree_x);
    controller.RotateForwardY(degree_y);
    controller.RotateForwardZ(degree_z);

    vertices = controller.GetVetrixCoordinate();
    surfaces = controller.GetSurfaceNum();
   } else {
     ui->error_xyz_scale->setText("Неверно введенные данные");
   }
   ui->view_window->update();
 //}
}

void MainWindow::on_pushButton_scale_clicked() {
 ui->error_xyz_scale->setText("");

 //if (checkFile()) {
   bool ratio_err;
   double ratio = ui->scale->text().toDouble(&ratio_err);

   if (ratio_err && ratio > 0) {
    controller.ScaleForward(ratio);

    vertices = controller.GetVetrixCoordinate();
    surfaces = controller.GetSurfaceNum();
  
   } else {
     ui->error_xyz_scale->setText("Неверно введенные данные");
   }
   ui->view_window->update();
 //}
}

//bool MainWindow::checkFile() {
//  bool status = false;

//  if (ui->file_name->text() != "" && data.count_vertices != 0 &&
//      data.count_surfaces != 0 && ui->error_file->text() == "") {
//    status = true;
//  }

//  return status;
//}

bool MainWindow::isAngles(double degree_x, double degree_y, double degree_z) {
  bool status = false;

  if (fabs(degree_x) >= 0 && fabs(degree_x) <= 360 && fabs(degree_y) >= 0 &&
      fabs(degree_y) <= 360 && fabs(degree_z) >= 0 && fabs(degree_z) <= 360) {
    status = true;
  }

  return status;
}

void MainWindow::on_projection_type_currentIndexChanged(int index) {
  emit projectionTypeChanged(index);
}

void MainWindow::on_width_edge_currentIndexChanged(int index) {
  emit widthEdgeChanged(index);
}

void MainWindow::on_line_type_currentIndexChanged(int index) {
  emit lineTypeChanged(index);
}

void MainWindow::on_size_vertices_currentIndexChanged(int index) {
  emit sizeVerticesChanged(index);
}

void MainWindow::on_vertices_type_currentIndexChanged(int index) {
  emit verticesTypeChanged(index);
}

