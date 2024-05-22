#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QLineSeries>

class SerialPortReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QPointF> m_data NOTIFY lineSeriesChanged)

public:
    explicit SerialPortReader(QObject *parent = nullptr);
    ~SerialPortReader();


public slots:
    void openSerialPort(const QString &portName);
    void closeSerialPort();
    void update(QAbstractSeries *series);
    Q_INVOKABLE QStringList availablePorts() const;

signals:
    void dataChanged();
    void lineSeriesChanged();

private slots:
    void readData();

private:
    QSerialPort *m_serialPort;
    QList<QPointF> m_data;
};

#endif
