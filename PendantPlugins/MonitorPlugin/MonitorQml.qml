import QtQuick 2.12

Rectangle{
    id: root
    property var itemBackgroundColor: "#DEFFFFFF"
    width: 400
    height: 665
    color:"#00FF0000"

    Rectangle{
        id: time
        color: root.itemBackgroundColor
        width: 155
        height: 155
        radius: 30
        anchors.margins: 20
        anchors.left: parent.left
        Text {
            id: time_text
            text: getCurrentTime()
            anchors.centerIn: time

        }
    }
    Rectangle{
        id: monitor
        color: root.itemBackgroundColor
        width: 155
        height: 155
        radius: 30
        anchors.margins: 20
        anchors.right: parent.right
        Text {
            id: monitor_xxx
            text: "hello" + methods.getUsername()
            anchors.top: parent.top
            anchors.topMargin: 15
        }
    }
    Rectangle{
        id: wether
        color: root.itemBackgroundColor
        width: parent.width - 40
        height: 130
        radius: 30
        anchors.left: parent.left
        anchors.top: time.bottom
        anchors.topMargin: 35
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        Text {
            id: wether_xxx
            text: qsTr("15:00")
            anchors.centerIn: wether
        }
    }

    Rectangle{
        id: dashboard
        color: root.itemBackgroundColor
        width: parent.width - 40
        height: 80
        radius: 30
        anchors.left: parent.left
        anchors.top: wether.bottom
        anchors.topMargin: 35
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        Text {
            id: dashboard_xxx
            text: qsTr("15:00")
            anchors.centerIn: dashboard
        }
    }

    function getCurrentTime(){
        return Qt.formatDateTime(new Date(), "hh:mm");

    }
    Timer{
        id: timer
        interval: 1000 //间隔(单位毫秒):1000毫秒=1秒
        repeat: true //重复
        onTriggered:{
            time_text.text = getCurrentTime();
        }
    }
    Component.onCompleted: {
        timer.start();
    }


}

