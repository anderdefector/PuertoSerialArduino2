#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->display("-----");

    serialBuffer = "";

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort(this);

    qDebug() << "Número de puertos disponibles " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "ID del Proveedor: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug()<< "ID del Proveedor: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Tiene ID de Producto: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "ID de Prodcuto: " << serialPortInfo.productIdentifier();
        }
        qDebug() << "Nombre del puerto utilizado: " << serialPortInfo.portName();
    }

    arduino->setPortName("/dev/ttyACM0");
    arduino->open(QSerialPort::ReadOnly);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    QObject::connect(arduino,SIGNAL(readyRead()),this, SLOT(readSerial()));

    if(arduino->isOpen()){
        qDebug() << "Arduino Disponible";
    }else{
        qDebug() << "No se pudo establecer la comunicación :(";
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSerial(){
    /*
    //qDebug() << "Serial Funciona";
    serialData = arduino->readAll();
    serialBuffer += QString::fromStdString(serialData.toStdString());
    qDebug()<<serialBuffer;
    */
  QStringList bufferSplit = serialBuffer.split(",");
  if(bufferSplit.length() < 3){
      serialData = arduino->readAll();
      serialBuffer += QString::fromStdString(serialData.toStdString());
  }else{
      qDebug() << bufferSplit;
      MainWindow::refreshLCD(bufferSplit[1]);
      serialBuffer = "";
  }

}

void MainWindow::refreshLCD(const QString lectura_sensor){

    ui->lcdNumber->display(lectura_sensor);
}

