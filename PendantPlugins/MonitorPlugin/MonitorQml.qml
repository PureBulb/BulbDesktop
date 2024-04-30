import QtQuick 2.12



Rectangle{
    id: parent
    property var itemBackgroundColor: "#f0f8ff"
    width: 400
    height: 500
    opacity: 1
    Rectangle{
        width: 380
        height: 100
        x: 10
        y: 10
        color: parent.itemBackgroundColor
    }
    Rectangle{
        width: 380
        height: 100
        x: 10
        y: 120
        color: parent.itemBackgroundColor
    }
    Rectangle{
        width: 380
        height: 100
        x: 10
        y: 230
        color: parent.itemBackgroundColor
    }


}

