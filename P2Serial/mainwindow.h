#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void readSerial();
    void refreshLCD(const QString lectura_sensor);

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 10755;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;

    QByteArray serialData;
    QString serialBuffer;
};

#endif // MAINWINDOW_H
