#include "serialportreader.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>

SerialPortReader::SerialPortReader(QObject *parent) : QObject(parent), m_serialPort(new QSerialPort(this)), m_lineSeries(new QLineSeries(this))
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::readData);
}

SerialPortReader::~SerialPortReader()
{
    closeSerialPort();
}

QString SerialPortReader::data() const
{
    return m_data;
}

QLineSeries* SerialPortReader::lineSeries() const
{
    return m_lineSeries;
}

QStringList SerialPortReader::availablePorts() const
{
    QStringList ports;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ports.append(info.portName());
    }
    return ports;
}

void SerialPortReader::openSerialPort(const QString &portName)
{
    m_serialPort->setPortName(portName);
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    if (m_serialPort->open(QIODevice::ReadOnly)) {
        qDebug() << "Serial port opened successfully";
    } else {
        qDebug() << "Failed to open serial port";
    }
}

void SerialPortReader::closeSerialPort()
{
    if (m_serialPort->isOpen())
        m_serialPort->close();
}

void SerialPortReader::readData()
{
    QByteArray data = m_serialPort->readAll();
    m_data = QString::fromLatin1(data);
    emit dataChanged();

    // Parse data and add to series
    bool ok;
    double value = m_data.toDouble(&ok);
    if (ok) {
        static qint64 startTime = QDateTime::currentMSecsSinceEpoch(); // Время начала
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch(); // Текущее время
        qint64 elapsedTime = currentTime - startTime; // Прошедшее время с начала
        double secondsElapsed = elapsedTime / 1000.0; // Прошедшее время в секундах
        // qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

        QPointF point(secondsElapsed, value);
        m_lineSeries->append(point);

        if (m_lineSeries->count() > 100)
            m_lineSeries->remove(0);

        qDebug() << secondsElapsed << value;
        emit lineSeriesChanged();
    }
}
