#include <iostream>
#include <QApplication>
#include <QWidget>

#include "src/main_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv); // создаем объект приложения
  MainWindow widget;
  widget.show();
  return app.exec();
}
