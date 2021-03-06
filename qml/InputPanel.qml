import QtQuick 2.9
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import "."

ColumnLayout {
    anchors.fill: parent

    MetaDataPanel {
        id: metaDataPanel
        Layout.alignment: Qt.AlignBottom
        isActive: model_input_line.metaUrlName != "" && model_input_line.inputText.length != 0
        metaHeader: model_input_line.metaUrlName
        metaTitle: model_input_line.metaUrlTitle
        metaImage: model_input_line.metaUrlImage
        onCancel: {
            model_input_line.inputText = ""
        }
    }

    Label {
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        text: model_input_line.inputText.length == 0 ? qsTr("Search field is empty") : (model_input_line.metaUrlName != "" ? "" : "loading...")
        visible: model_input_line.metaUrlName == ""
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignBottom
        Layout.margins: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: textInputRow.height + 20
            color: "gray"
            radius: 10

            RowLayout {
                anchors.rightMargin: 15
                anchors.leftMargin: 15
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                RowLayout {
                    id:textInputRow
                    Layout.fillWidth: true

                    TextEdit {
                        id:textInputField
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignLeft
                        text: model_input_line.inputText
                        wrapMode: TextInput.Wrap
                        selectByMouse: true
                        color: "white"
                        font.pointSize: 12
                        onTextChanged: {
                            if(model_input_line.inputText != text) {
                                model_input_line.inputText = text
                            }
                        }
                    }
                }
            }
        }
    }
}
