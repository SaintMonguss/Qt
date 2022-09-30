import QtQuick 2.0

Rectangle {
    id: slider
    property int itemAngle: 60
    property int itemSize: 220

    width: 400;
    height: 100;
    signal itemSelected(string path)

    function decrementCurrentIndex() {
        view.decrementCurrentIndex();
    }

    function incrementCurrentIndex() {
        view.incrementCurrentIndex();
    }

    focus: true
    Keys.onLeftPressed: view.decrementCurrentIndex();
    Keys.onRightPressed: view.incrementCurrentIndex();

    PathView {
        id: view
        objectName: "view"
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        model: dataModel
        pathItemCount: 6
        cacheItemCount: 30

        interactive: true

        path: Path {
            startX: 0
            startY: height / 2

            PathPercent { value: 0.0 }
            PathAttribute { name: "z"; value: 0 }
            PathAttribute { name: "angle"; value: itemAngle }
            PathAttribute { name: "origin"; value: 0 }
            PathAttribute { name: "scale"; value: 0.8; }
            PathLine {
                x: (view.width - itemSize) / 2
                y: view.height / 2
            }
            PathAttribute { name: "angle"; value: itemAngle }
            PathAttribute { name: "origin"; value: 0 }
            PathPercent { value: 0.40 }                 // 49
            PathAttribute { name: "z"; value: 10 }
            PathAttribute { name: "scale"; value: 1.0; }

            PathLine { relativeX: 0; relativeY: 0 }

            PathAttribute { name: "angle"; value: 0 }
            PathLine {
                x: (view.width - itemSize) / 2 + itemSize
                y: view.height / 2
            }
            PathAttribute { name: "angle"; value: 0 }
            PathPercent { value: 0.60 }                 // 51

            PathLine { relativeX: 0; relativeY: 0 }

            PathAttribute { name: "z"; value: 10 }
            PathAttribute { name: "angle"; value: -itemAngle }
            PathAttribute { name: "origin"; value: itemSize }
            PathAttribute { name: "scale"; value: 1.0; }
            PathLine {
                x: view.width
                y: view.height / 2
            }
            PathPercent { value: 1 }
            PathAttribute { name: "z"; value: 0 }
            PathAttribute { name: "angle"; value: -itemAngle }
            PathAttribute { name: "origin"; value: itemSize }
            PathAttribute { name: "scale"; value: 0.8; }
        }

        delegate: Item {
            property real rotationAngle: PathView.angle
            property real rotationOrigin: PathView.origin
            z: PathView.z
            visible: PathView.onPath
            scale: PathView.scale

            width: itemSize
            height: width

//            color: "white"
//            border { color: "black"; width: 1; }

            transform: Rotation {
                axis { x: 0; y: 1; z: 0 }
                angle: rotationAngle
                origin.x: width/2
                origin.y: height/2
            }

            Image {
                id: image
                anchors { fill: parent; bottomMargin: parent.height * 0.04
                    rightMargin: 10; leftMargin: 10; }
                fillMode:Image.PreserveAspectFit
                source: model.modelData.path
            }

            Text {
                id: text
                height: parent.height * 0.08;
                anchors { top: image.bottom; left: parent.left;
                    right: parent.right; bottom: parent.bottom; }
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: parent.height*0.07
                text: model.modelData.name
            }

            MouseArea {
                anchors.fill: parent
                onClicked:
//                    if(parent.scale >= 8.0)
                        slider.itemSelected(model.modelData.path)
            }
        }
    }
}
