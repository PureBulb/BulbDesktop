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
        Rectangle{
            id: time_info
            width: 80
            height: 50
            color: '#00000000'
            anchors.centerIn: time
            Text {
                id: time_text
                text: getCurrentTime()
                font.pointSize: 22
                //anchors.horizontalCenter: parent
            }
            Text{
                id: time_describe
                text: qsTr("Local Time")
                font.pointSize: 10
                anchors.bottom: time_info.bottom
                leftPadding: 5
            }
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
            id: monitor_user
            text: "hello: " + methods.getUsername()
            anchors.top: parent.top
            anchors.topMargin: 20
            font.weight: Font.Bold
            leftPadding: 15
            font.pointSize: 10
        }
        Text {
            id: monitor_cpu
            text: "cpu: " + (methods.getCpuUsage()*100 ).toFixed(2)+"%"
            anchors.top: monitor_user.bottom
            anchors.topMargin: 20
            font.weight: Font.Bold
            leftPadding: 15
            font.pointSize: 10
        }
        Text {
            id: monitor_memory
            text: "memory: " + methods.getMemoryRate() +"%"
            anchors.top: monitor_cpu.bottom
            anchors.topMargin: 20
            font.weight: Font.Bold
            leftPadding: 15
            font.pointSize: 10
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
            monitor_cpu.text =  "cpu: " + (methods.getCpuUsage()*100).toFixed(2) +"%"
            monitor_memory.text = "memory: " + methods.getMemoryRate() +"%"


        }
    }
    Component.onCompleted: {
        timer.start();
    }


}

