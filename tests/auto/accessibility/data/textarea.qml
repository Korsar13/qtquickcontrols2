import QtQuick 2.5
import QtQuick.Window 2.2
import Qt.labs.controls 1.0

Window {
    visible: true

    TextArea {
        id: textarea
        objectName: "textarea"
        text: "TextArea"
        Accessible.name: text
    }
}
