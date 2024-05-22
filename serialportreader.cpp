#include "serialportreader.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <QXYSeries>

Q_DECLARE_METATYPE(QAbstractSeries *)

SerialPortReader::SerialPortReader(QObject *parent) : QObject(parent), m_serialPort(new QSerialPort(this))
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::readData);
    qRegisterMetaType<QAbstractSeries*>();
}

SerialPortReader::~SerialPortReader()
{
    closeSerialPort();
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

void SerialPortReader::update(QAbstractSeries *series)
{
    if (series) {
        auto xySeries = static_cast<QXYSeries *>(series);

        QList<QPointF> points = m_data;
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(points);
    }
}

void SerialPortReader::readData()
{
    QByteArray line;

    QList<QPointF> points;
    points.reserve(5000-1000);

    int i = 1000;
    if (m_serialPort->canReadLine()) {
        while (m_serialPort->canReadLine()) {
            line = m_serialPort->readLine().trimmed();

            points.append(QPointF(i, line.toFloat()));

            i++;

            if (i > 5000) {
                m_data = points;
                qDebug() << "jopa";
                emit lineSeriesChanged();
            }
        }

    }



    // m_data = QString::fromLatin1(data);
    // emit dataChanged();

    // Parse data and add to series
    // bool ok;
    // double value = m_data.toDouble(&ok);
//     if (ok) {
//         static qint64 startTime = QDateTime::currentMSecsSinceEpoch(); // Время начала
//         qint64 currentTime = QDateTime::currentMSecsSinceEpoch(); // Текущее время
//         qint64 elapsedTime = currentTime - startTime; // Прошедшее время с начала
//         double secondsElapsed = elapsedTime / 1000.0; // Прошедшее время в секундах
//         // qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

//         // QPointF point(secondsElapsed, value);

//         m_lineSeries->removePoints(0,10000);
//         qDebug() << value;
//         for (int i=0; i < 10000; i++) {

//         }

//         // m_lineSeries->append(point);

//         // if (m_lineSeries->count() > 100)
//         //     m_lineSeries->remove(0);

//         qDebug() << secondsElapsed << value;

//     }
}
