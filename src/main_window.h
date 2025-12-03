#ifndef COM_PORT_LESSON__MAIN_WINDOW_H_
#define COM_PORT_LESSON__MAIN_WINDOW_H_

#include <QMainWindow>

class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget *parent = nullptr);

 private:
  void initUi();

//  QPushButton *_my_btn = nullptr;
};

#endif //COM_PORT_LESSON__MAIN_WINDOW_H_
