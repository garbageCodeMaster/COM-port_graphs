#include "COMemulator.h"
#include <QCoreApplication>

COMemulator::COMemulator(QObject *parent) : QObject(parent) {
    // Setup the serial port (adjust as needed)
    serialPort.setPortName("COM1"); // Use a name that matches the virtual serial port on your system
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    // Open the port (for demonstration, we are not actually connecting to hardware)
    if (!serialPort.open(QIODevice::ReadWrite)) {
        qCritical() << "Failed to open port";
        return;
    }

    // Timer to emulate data reception
    connect(&timer, &QTimer::timeout, this, &COMemulator::emitFakeData);
    timer.start(1000); // Emulate data every second

    // Read data from the serial port
    // connect(&serialPort, &QSerialPort::readyRead, this, &COMemulator::readData);
}

void COMemulator::emitFakeData() {
    QByteArray fakeData;

    for (int i = 1000; i < 5000; ++i) {
        // Generate random floating-point number between 0 and 200
        qreal randomValue = QRandomGenerator::global()->generateDouble() * 200.0;

        // Append the generated value to the fake data, formatted to 4 significant digits
        fakeData += QByteArray::number(randomValue, 'g', 4) + '\n';
    }

    // Write the accumulated fake data to the serial port
    serialPort.write(fakeData);
}

