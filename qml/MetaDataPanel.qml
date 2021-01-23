import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import "./"
import "./../"
import "./../../"

Rectangle {
    id : root
    Layout.preferredHeight: 70
    Layout.fillWidth: true

    property bool isActive: false
    property string metaHeader: ""
    property string metaTitle: ""
    property string metaImage: ""

    visible: isActive

    signal cancel()

    color: "gray"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        Image {
            source: "qrc:/images/images/stop_gray.svg"
            sourceSize.width: 14; sourceSize.height: 14
            Layout.margins: 10
            Layout.alignment: Qt.AlignLeft
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignLeft

            Label {
                text: metaHeader
                color: "black"
                elide: Text.ElideRight
                Layout.preferredWidth: (root.width - 150)
                font.pixelSize: 10
            }

            Label {
                text: metaTitle
                elide: Text.ElideRight
                Layout.preferredWidth: (root.width - 150)
                color: "black"
                font.pixelSize: 15
                wrapMode: TextEdit.Wrap
                maximumLineCount: 1
            }
        }

        Image {
            source: metaImage
            sourceSize.width: 50; sourceSize.height: 50
        }
    }
}
