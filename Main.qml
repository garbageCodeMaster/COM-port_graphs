import QtQuick 2.15
import QtQuick.Controls 2.15
import QtDataVisualization 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    Surface3D {
        id: graph
        width: parent.width
        height: parent.height

        axes: [
            ValueAxis3D {
                minValue: 0
                maxValue: 10
                title: "Frequency (MHz)"
            },
            ValueAxis3D {
                minValue: 0
                maxValue: 10
                title: "Time"
            },
            ValueAxis3D {
                minValue: -1
                maxValue: 1
                title: "Amplitude"
            }
        ]

        surfaceSeriesList: [
            Surface3DSeries {
                mesh: Surface3DSeries.MeshSurface
                dataProxy: ItemModelSurfaceDataProxy {
                    itemLabelFormat: "Amplitude @ (Frequency, Time): %1"
                    rowCount: 100
                    columnCount: 100

                    // Here you would fill in your data
                    // In a real application, you would likely load this data from a file or generate it dynamically
                    itemArray: ListModel {
                        ListElement { value: Math.sin(0) }
                        ListElement { value: Math.sin(0.1) }
                        ListElement { value: Math.sin(0.2) }
                        // ... (add more data points as needed)
                    }
                }
            }
        ]
    }
}
