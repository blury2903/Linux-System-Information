import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MyUptime 1.0
import MyMemory 1.0
import MyCpuInfo 1.0
import MyKernelVersion 1.0
import MyTimeStamp 1.0
import MyOsInfo 1.0

Window {
    width: 320
    height: 240
    visible: true
    title: qsTr("System Information")

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 5
        rows: 2
        columns: 3

        GroupBox {
            id: kernelBox
            Layout.fillHeight: true
            Layout.fillWidth: true
            padding: 5
            label: Label {
                topPadding: 5
                bottomPadding: -5

                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    bold: true
                    pixelSize: 15
                }
                text: "KERNEL"

            }

            ColumnLayout {
                anchors.fill: parent
                Text {
                    Layout.fillWidth: true
                    text:(kernelVersionId === null ? "" : kernelVersionId.kernelVersion)
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                }
            }

        }
        GroupBox {
            id: upTimeBox
            Layout.fillHeight: true
            Layout.fillWidth: true
            label: Label {
                topPadding: 5
                bottomPadding: -5
                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    bold: true
                    pixelSize: 15
                }
                text: "UPTIME"

            }
            Text {
                anchors.centerIn: parent
                Layout.fillWidth: true
                text: (upTimeId === null ? "" : upTimeId.upTime)
                font.pixelSize: 10
            }

        }

        GroupBox {
            id: timeBox
            Layout.fillHeight: true
            Layout.fillWidth: true
            label: Label {
                topPadding: 5
                bottomPadding: -5
                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    bold: true
                    pixelSize: 15
                }
                text: "TIME"

            }
            Text {
                anchors.centerIn: parent
                text: (timeStampId === null ? "" : timeStampId.timeStamp)
                font.pixelSize: 10
            }

        }


        GroupBox {
            id: osBox
            Layout.fillHeight: true
            Layout.fillWidth: true
            // Layout.columnSpan: 2
            label: Label {
                topPadding: 5
                bottomPadding: -5

                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    bold: true
                    pixelSize: 15
                }
                text: "OS"

            }

            ColumnLayout {
                anchors.fill: parent
                anchors.centerIn: parent

                Text {
                    Layout.fillWidth: true
                    text: "Name: " + (osInfoId === null ? "" : osInfoId.osName)
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                }

                Text {
                    Layout.fillWidth: true
                    text: "Ver: " + (osInfoId === null ? "" : osInfoId.osVersion)
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                }

            }

        }


        GroupBox {
            id: cpuBox
            Layout.fillHeight: true
            Layout.fillWidth: true
            // Layout.columnSpan: 2
            label: Label {
                topPadding: 5
                bottomPadding: -5

                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    bold: true
                    pixelSize: 15
                }
                text: "CPU"

            }

            ColumnLayout {
                anchors.fill: parent

                Text {
                    Layout.fillWidth: true
                    text: "Name: " + (cpuInfoId === null ? "" : cpuInfoId.modelName)
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                }

                Text {
                    Layout.fillWidth: true
                    text: cpuInfoId.serial === "" ? "" : ("Serial: " + cpuInfoId.serial)
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                }

            }

        }


        GroupBox {
            id: memoryBox
            Layout.fillHeight: true
            // Layout.fillWidth: true
            label: Label {
                topPadding: 5
                bottomPadding: -5

                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    bold: true
                    pixelSize: 15
                }
                text: "MEMORY"

            }

            ColumnLayout {
                anchors.fill: parent
                Text {
                    id: totalMemTextId
                    text: "Total: "
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                    Layout.fillWidth: true
                }

                Text {
                    id: freeMemTextId
                    text: "Free: "
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                    Layout.fillWidth: true
                }

                Text {
                    id: usageMemTextId
                    text: "Usage: "
                    font.pixelSize: 10
                    wrapMode: "WordWrap"
                    Layout.fillWidth: true
                }
            }

        }



    }





    UpTime {
        id: upTimeId
    }

    CpuInfo {
        id: cpuInfoId
    }

    KernelVersion {
        id: kernelVersionId
    }

    Memory {
        id: memId
        onMemoryChanged: {

            var key = "MemTotal"
            totalMemTextId.text = "Total: " + dataFromCpp(key) + " GB"

            key = "MemFree"
            freeMemTextId.text = "Free: " + dataFromCpp(key) + " GB"

            key = "MemUsage"
            usageMemTextId.text = "Usage: " + dataFromCpp(key) + "%"

        }

    }

    TimeStamp {
        id: timeStampId
    }

    OsInfo {
        id: osInfoId
    }


}
