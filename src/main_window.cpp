#include <QPushButton>
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  initUi();
}
void MainWindow::initUi() {
  QPushButton *my_btn = new QPushButton("Button 1", this);
}
