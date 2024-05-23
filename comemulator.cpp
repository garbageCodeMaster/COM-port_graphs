#include "COMemulator.h"

#include <algorithm>
#include <random>
#include <math.h>
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




    for (int i = 1000; i < 5000; ++i) {
        indices.append(i);
    }
    // Перемешивание индексов
    //std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});




    // Timer to emulate data reception
    connect(&timer, &QTimer::timeout, this, &COMemulator::emitFakeData);
    timer.start(100); // Emulate data every second

    // Read data from the serial port
    // connect(&serialPort, &QSerialPort::readyRead, this, &COMemulator::readData);
}

void COMemulator::emitFakeData() {
    QByteArray fakeData;

    for (int i = 0; i < indices.size(); ++i) {
        qreal u1 = QRandomGenerator::global()->generateDouble(); // Случайное число от 0 до 1

        double coefficient = 1 / (std::sqrt(2 * M_PI) * 15);
        double exponent = std::exp(-0.5 * std::pow((float(i - 2000)/30) / 15, 2));

        double w = coefficient * exponent;
        qreal randomValue = 500.0 * w + (u1 > 0.7 ? u1*3: u1*2); // Преобразование в значение с нужным средним и стандартным отклонением
        fakeData += QByteArray::number(randomValue, 'g', 4) + '\n';
    }

    serialPort.write(fakeData);
}
