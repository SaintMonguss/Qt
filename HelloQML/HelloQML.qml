import QtQuick

Rectangle {
    id : page
    width: 200
    height: 200
    color: "lightgray"
    border.color: "black"
    border.width: 5
    radius: 10

    Text
    {
        id: helloText
        x : 66
        y : 93
        text: "Hello World"
        color : "azure"
        anchors.horizontalCenter: page.horizontalCenter
        font { pointSize : 24; bold: true}
    }

    Grid
    {
        id :colorPicker
        x: 4
        anchors.bottom: page.bottom
        anchors.bottomMargin : 4
        rows: 2
        columns: 3
        spacing : 3

        Cell{cellColor: "red"; onClicked: helloText.color =cellColor}
        Cell{cellColor: "green"; onClicked: helloText.color =cellColor}
        Cell{cellColor: "blue"; onClicked: helloText.color =cellColor}
        Cell{cellColor: "yellow"; onClicked: helloText.color =cellColor}
        Cell{cellColor: "steelblue"; onClicked: helloText.color =cellColor}
        Cell{cellColor: "black"; onClicked: helloText.color =cellColor}
    }
}
