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
    Q_PROPERTY(QString data READ data NOTIFY dataChanged)
    Q_PROPERTY(QLineSeries* lineSeries READ lineSeries NOTIFY lineSeriesChanged)

public:
    explicit SerialPortReader(QObject *parent = nullptr);
    ~SerialPortReader();

    QString data() const;
    QLineSeries* lineSeries() const;

public slots:
    void openSerialPort(const QString &portName);
    void closeSerialPort();
    Q_INVOKABLE QStringList availablePorts() const;

signals:
    void dataChanged();
    void lineSeriesChanged();

private slots:
    void readData();

private:
    QSerialPort *m_serialPort;
    QString m_data;
    QLineSeries *m_lineSeries;
};

#endif
