#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("3D_Viewer");

  connect(ui->pushButton_color_edges, &QPushButton::clicked, this, &MainWindow::openColorDialogEdges);
  connect(ui->pushButton_color_vertices, &QPushButton::clicked, this, &MainWindow::openColorDialogVertices);
  connect(ui->pushButton_color_back, &QPushButton::clicked, this, &MainWindow::openColorDialogBackground);
  connect(&colorDialog, &QColorDialog::colorSelected, this, &MainWindow::colorSelected);
  connect(this, SIGNAL(colorChanged(int, const QColor)), ui->view_window, SLOT(onColorChanged(int, const QColor)));

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

    printf("%d\n", edges_color.red());
    printf("%d\n",  edges_color.green());
    printf("%d\n", edges_color.blue());
  //  settings.setValue("edges_color", edges_color);
  //  settings.setValue("vertices_color", vertices_color);
  //  settings.setValue("background_color", background_color);

  settings.setValue("edges_color_red", edges_color.red());
  settings.setValue("edges_color_green", edges_color.green());
  settings.setValue("edges_color_blue", edges_color.blue());

  settings.setValue("vertices_color_red", vertices_color.red());
  settings.setValue("vertices_color_green", vertices_color.green());
  settings.setValue("vertices_color_blue", vertices_color.blue());

  settings.setValue("background_color_red", background_color.red());
  settings.setValue("background_color_green", background_color.green());
  settings.setValue("background_color_blue", background_color.blue());

 // edges_color = settings.value("edges_color", QColor(0, 0, 0)).value<QColor>();
 // vertices_color = settings.value("vertices_color", QColor(255, 0, 0)).value<QColor>();
 // background_color = settings.value("background_color", QColor(255, 255, 255)).value<QColor>();


  //  printf("%d\n", edges_color.red());
  //  printf("%d\n",  edges_color.green());
  //  printf("%d\n", edges_color.blue());
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

    int edges_red = settings.value("edges_color_red", 0).toInt();
    int edges_green = settings.value("edges_color_green", 0).toInt();
    int edges_blue = settings.value("edges_color_blue", 0).toInt();
    edges_color = QColor(edges_red, edges_green, edges_blue);

    int vertices_red = settings.value("vertices_color_red", 255).toInt();
    int vertices_green = settings.value("vertices_color_green", 0).toInt();
    int vertices_blue = settings.value("vertices_color_blue", 0).toInt();
    vertices_color = QColor(vertices_red, vertices_green, vertices_blue);

    int background_red = settings.value("background_color_red", 255).toInt();
    int background_green = settings.value("background_color_green", 255).toInt();
    int background_blue = settings.value("background_color_blue", 255).toInt();
    background_color = QColor(background_red, background_green, background_blue);

   // edges_color = settings.value("edges_color", QColor(0, 0, 0)).value<QColor>();
   // vertices_color = settings.value("vertices_color", QColor(255, 0, 0)).value<QColor>();
   // background_color = settings.value("background_color", QColor(255, 255, 255)).value<QColor>();

    printf("%d\n", edges_color.red());
    printf("%d\n",  edges_color.green());
    printf("%d\n", edges_color.blue());
    emit colorChanged(0, edges_color);
    emit colorChanged(1, vertices_color);
    emit colorChanged(2, background_color);
}

void MainWindow::openColorDialogEdges() {
  currentParam = 0;
  colorDialog.show();
}

void MainWindow::openColorDialogVertices() {
  currentParam = 1;
  colorDialog.show();
}

void MainWindow::openColorDialogBackground() {
  currentParam = 2;
  colorDialog.show();
}

void MainWindow::colorSelected(const QColor &color) {
  switch (currentParam) {
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

  emit colorChanged(currentParam, color);
}

void MainWindow::on_pushButton_file_clicked() {
  setDefaultSettings();
  controller.Clear();

  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/", tr("Files (*.obj)"));

  if (file_name != "") {
    std::string file_name_string = file_name.toStdString();
    controller.SetData(file_name_string);

    ui->file_name->setText(getFileName(file_name));

    vertices = controller.GetVetrixCoordinate();
    surfaces = controller.GetSurfaceNum();
    amount_surfaces = controller.GetAmountSurfaces();
    amount_edges = controller.GetAmountEdges();

    ui->count_vertices->setText(QString::number(vertices.size() - 1));
    ui->count_edges->setText(QString::number(amount_edges));

    if (vertices.size() - 1 != 0 && amount_surfaces != 0) {
        ui->view_window->sendData(vertices, surfaces, amount_surfaces);
        ui->view_window->update();
    } else if (vertices.size() - 1 == 0 && amount_surfaces == 0) {
      ui->error_file->setText("Файл пустой");
    } else {
      ui->error_file->setText("Недостаточно данных");
    }
  } else {
    ui->error_file->setText("Откройте файл");
  }
}

void MainWindow::setDefaultSettings() {
  ui->error_file->setText("");
  ui->error_xyz_scale->setText("");
  ui->file_name->setText("");
  ui->count_vertices->setText("");
  ui->count_edges->setText("");
  ui->x_move->setText("0");
  ui->y_move->setText("0");
  ui->z_move->setText("0");
  ui->x_rotate->setText("0");
  ui->y_rotate->setText("0");
  ui->z_rotate->setText("0");
  ui->scale->setText("1");

  ui->view_window->setupOpenGLState();
}

QString MainWindow::getFileName(QString file_name) {
  QStringList splited_str = file_name.split("/");
  file_name = splited_str.last();
  return file_name;
}

void MainWindow::on_pushButton_move_clicked() {
 ui->error_xyz_scale->setText("");

 if (checkFile()) {
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
   ui->view_window->sendData(vertices, surfaces, amount_surfaces);
   ui->view_window->update();
 }
}

void MainWindow::on_pushButton_rotate_clicked() {
 ui->error_xyz_scale->setText("");

 if (checkFile()) {
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
   ui->view_window->sendData(vertices, surfaces, amount_surfaces);
   ui->view_window->update();
 }
}

void MainWindow::on_pushButton_scale_clicked() {
 ui->error_xyz_scale->setText("");

 if (checkFile()) {
   bool ratio_err;
   double ratio = ui->scale->text().toDouble(&ratio_err);

   if (ratio_err && ratio > 0) {
    controller.ScaleForward(ratio);

    vertices = controller.GetVetrixCoordinate();
    surfaces = controller.GetSurfaceNum();
  
   } else {
     ui->error_xyz_scale->setText("Неверно введенные данные");
   }
   ui->view_window->sendData(vertices, surfaces, amount_surfaces);
   ui->view_window->update();
 }
}

bool MainWindow::checkFile() {
 bool status = false;

 if (ui->file_name->text() != "" && vertices.size() - 1 != 0 &&
     amount_surfaces != 0 && ui->error_file->text() == "") {
   status = true;
 }

 return status;
}

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

