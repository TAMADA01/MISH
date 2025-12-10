#include "main_window.h"

#include <QMessageBox>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  serialPort = new QSerialPort(this);
  initUi();
  initConnections();
  scanPorts();
}

MainWindow::~MainWindow() {
  if (serialPort->isOpen()) {
    serialPort->close();
  }
}

void MainWindow::initUi() {
  // Создаем центральный виджет для QMainWindow
  auto central_widget = new QWidget(this);

  main_layout = new QHBoxLayout();
  connection_layout = new QVBoxLayout();
  communicate_layout = new QVBoxLayout();

  com_port_cb = new QComboBox();
  scan_btn = new QPushButton("Scan Ports");
  connect_btn = new QPushButton("Connect");
  disconnect_btn = new QPushButton("Disconnect");
  disconnect_btn->setEnabled(false);

  conn_btn_layout = new QHBoxLayout();
  conn_btn_layout->addWidget(connect_btn);
  conn_btn_layout->addWidget(disconnect_btn);

  // Layout для портов
  auto port_layout = new QHBoxLayout();
  port_layout->addWidget(com_port_cb);
  port_layout->addWidget(scan_btn);

  auto conn_layout = new QVBoxLayout();

  status_label = new QLabel("Status: Disconnected");

  conn_layout->addLayout(port_layout);
  conn_layout->addLayout(conn_btn_layout);
  conn_layout->addWidget(status_label);

  connection_group = new QGroupBox("Connection group");
  connection_group->setLayout(conn_layout);
  connection_layout->addWidget(connection_group);
  connection_layout->addStretch(0);

  // Для ввода текста для отправки
  text_edit = new QTextEdit();
  text_edit->setPlaceholderText("Enter text to send...");
  text_edit->setMaximumHeight(50);

  // Для отображения полученных данных
  received_text = new QTextEdit();
  received_text->setPlaceholderText("Received data will appear here...");
  received_text->setReadOnly(true);
  received_text->setMaximumHeight(50);

  write_btn = new QPushButton("Write to Port");

  auto comm_layout = new QVBoxLayout();

  comm_layout->addWidget(new QLabel("Received:"));
  comm_layout->addWidget(received_text);
  comm_layout->addWidget(new QLabel("Send:"));
  comm_layout->addWidget(text_edit);
  comm_layout->addWidget(write_btn);

  communication_group = new QGroupBox("Read/Write");
  communication_group->setLayout(comm_layout);

  communicate_layout->addWidget(communication_group);

  main_layout->addLayout(connection_layout);
  main_layout->addSpacing(10);
  main_layout->addLayout(communicate_layout);

  // Устанавливаем layout на центральный виджет
  central_widget->setLayout(main_layout);

  // Устанавливаем центральный виджет для QMainWindow
  setCentralWidget(central_widget);

  // Настройки окна
  setWindowTitle("COM Port Communicator");
//  resize(800, 600);
}

void MainWindow::initConnections() {
  // Подключаем кнопки к слотам
  connect(scan_btn, &QPushButton::clicked, this, &MainWindow::scanPorts);
  connect(connect_btn, &QPushButton::clicked, this, &MainWindow::connectToPort);
  connect(disconnect_btn, &QPushButton::clicked, this, &MainWindow::disconnectFromPort);

  // Подключаем сигналы от serial port
  connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
  connect(serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
}

void MainWindow::scanPorts() {
  com_port_cb->clear();

  // Получаем список доступных портов
  QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

  if (ports.isEmpty()) {
    com_port_cb->addItem("No ports found");
    connect_btn->setEnabled(false);
  } else {
    for (const QSerialPortInfo &port : ports) {
      QString info = port.portName() + " - " + port.description();
      com_port_cb->addItem(info, port.portName());
    }
    connect_btn->setEnabled(true);
  }
}

void MainWindow::connectToPort() {
  if (com_port_cb->currentIndex() < 0) {
    QMessageBox::warning(this, "Warning", "Please select a COM port first!");
    return;
  }

  QString portName = com_port_cb->currentData().toString();
  serialPort->setPortName(portName);

  // Настройки порта (можно вынести в отдельные настройки)
  serialPort->setBaudRate(QSerialPort::Baud9600);
  serialPort->setDataBits(QSerialPort::Data8);
  serialPort->setParity(QSerialPort::NoParity);
  serialPort->setStopBits(QSerialPort::OneStop);
  serialPort->setFlowControl(QSerialPort::NoFlowControl);

  if (serialPort->open(QIODevice::ReadWrite)) {
    isConnected = true;
    status_label->setText("Status: Connected to " + portName);
    connect_btn->setEnabled(false);
    disconnect_btn->setEnabled(true);
    write_btn->setEnabled(true);

    QMessageBox::information(this, "Success", "Connected to " + portName);
  } else {
    QMessageBox::critical(this, "Error", "Failed to connect to " + portName + "\nError: " + serialPort->errorString());
  }
}

void MainWindow::disconnectFromPort() {
  if (serialPort->isOpen()) {
    serialPort->close();
  }

  isConnected = false;
  status_label->setText("Status: Disconnected");
  connect_btn->setEnabled(true);
  disconnect_btn->setEnabled(false);
  write_btn->setEnabled(false);

  QMessageBox::information(this, "Disconnected", "Port closed successfully");
}

void MainWindow::handleReadyRead() {
  // Автоматически читаем данные при их поступлении
  QByteArray data = serialPort->readAll();
  QString text = QString::fromUtf8(data);

  if (!text.isEmpty()) {
    received_text->append("Auto-received: " + text.trimmed());
  }
}

void MainWindow::handleError(QSerialPort::SerialPortError error) {
  if (error == QSerialPort::ResourceError) {
    QMessageBox::critical(this, "Error", "Port error: " + serialPort->errorString());
    disconnectFromPort();
  }
}