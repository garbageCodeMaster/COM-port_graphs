// main.qml
// https://youtu.be/Kq0pX3Vhq0c?feature=shared
// https://forum.qt.io/topic/129576/custom-qml-chart-realtime-data/3
// https://github.com/Furkanzmc/QML-Coding-Guide

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.3
import SerialPortReader 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("COM Port Reader")

    SerialPortReader {
        id: serialPortReader

        onLineSeriesChanged: {
            // console.log(serialPortReader.lineSeries);
            serialPortReader.update(chartView.series(0));
            // dataSource.update(chartView.series(1));
        }
    }

    ChartView {
        id: chartView
        width: parent.width
        height: parent.height - 50
        antialiasing: true

        LineSeries {
            id: lineSeries2
            name: "COM Data"
            // useOpenGL: true
            ValueAxis {
                id: axisy
                min: 0
                max: 200
                gridVisible: true
                tickCount: 7
                titleText: "Power"
                titleFont.bold: true
                titleFont.italic: true
                titleFont.pointSize: 10
                }

            ValueAxis {
                id: axisx
                gridVisible: true
                // format: "hh:mm:ss"
                tickCount: 11
                titleText: "Mhz"
                titleFont.bold: true
                titleFont.italic: true
                titleFont.pointSize: 10
                max: 10000
                min: 0
            }

            axisX: axisx
            axisY: axisy

        }
    }


    ComboBox {
        id: portSelector
        width: parent.width
        model: serialPortReader.availablePorts()

        onActivated: {
            serialPortReader.closeSerialPort()
            serialPortReader.openSerialPort(portSelector.currentText)
        }
    }

    // Component.onCompleted: {
    //     console.log("Starting to read from COM port");
    //     if (portSelector.count > 0) {
    //         serialPortReader.readData(portSelector.currentText)
    //     }
    // }
}
