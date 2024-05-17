#ifndef COMEMULATOR_H
#define COMEMULATOR_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QByteArray>
#include <QDebug>
#include <QRandomGenerator>

class COMemulator : public QObject {
    Q_OBJECT

public:
    explicit COMemulator(QObject *parent = nullptr);

private slots:
    void emitFakeData();

private:
    QSerialPort serialPort;
    QTimer timer;
};

#endif
