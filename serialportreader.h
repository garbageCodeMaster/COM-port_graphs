#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QElapsedTimer>
#include <QPointF>

QT_FORWARD_DECLARE_CLASS(QAbstractSeries)
QT_FORWARD_DECLARE_CLASS(QXYSeries)

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
    void fpsChanged(const QString &fps);

private slots:
    void readData();

private:
    QSerialPort *m_serialPort;
    QList<QPointF> m_data;
    QElapsedTimer m_fpsTimer;
    QString m_fpsLabel;
};

#endif
