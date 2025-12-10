#ifndef COM_PORT_LESSON__MAIN_WINDOW_H_
#define COM_PORT_LESSON__MAIN_WINDOW_H_

#include <QMainWindow>
#include <QSerialPort>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void scanPorts();
  void connectToPort();
  void disconnectFromPort();
  void handleReadyRead();
  void handleError(QSerialPort::SerialPortError error);

 private:
  void initUi();
  void initConnections();

  // UI элементы
  QPushButton *connect_btn = nullptr;
  QPushButton *disconnect_btn = nullptr;
  QPushButton *write_btn = nullptr;
  QPushButton *scan_btn = nullptr;
  QComboBox *com_port_cb = nullptr;
  QTextEdit *text_edit = nullptr;
  QTextEdit *received_text = nullptr;
  QLabel *status_label = nullptr;

  // Layouts
  QHBoxLayout *main_layout = nullptr;
  QGroupBox *connection_group = nullptr;
  QGroupBox *communication_group = nullptr;
  QVBoxLayout *connection_layout = nullptr;
  QVBoxLayout *communicate_layout = nullptr;
  QHBoxLayout *conn_btn_layout = nullptr;

  // Для работы с COM-портом
  QSerialPort *serialPort = nullptr;
  bool isConnected = false;
};

#endif //COM_PORT_LESSON__MAIN_WINDOW_H_
