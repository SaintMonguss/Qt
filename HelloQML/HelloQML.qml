import QtQuick

Rectangle {
    id : page
    width: 200
    height: 200
    color : "black"
    Text
    {
        id: helloText
        x : 66
        y : 93
        text: "Hello World"
        color : "azure"
        anchors.horizontalCenter: page.horizontalCenter
        font.pointSize: 24
        font.bold: true
    }
}
