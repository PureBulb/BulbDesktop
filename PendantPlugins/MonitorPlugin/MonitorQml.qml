import QtQuick 2.12
import "qrc:/MonitorPlugin/Module/"
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
            width: parent.width
            text: "hello: " + methods.getUsername()
            anchors.top: parent.top
            anchors.topMargin: 20
            font.bold: true
            leftPadding: 15
            font.pointSize: 10
            elide: Text.ElideRight
        }
        Rectangle{
            id: monitor_cpu
            anchors.top: monitor_user.bottom
            width: parent.width
            height: 50
            color: '#00000000'
            Text {
                id: monitor_cpu_text
                text: "cpu: " + (methods.getCpuUsage()*100 ).toFixed(2)+"%"
                anchors.topMargin: 20
                font.bold: true
                leftPadding: 15
                font.pointSize: 10
            }
            Text{
                id: monitor_cpu_graph
                anchors.top: monitor_cpu_text.bottom
                leftPadding: 15
                text: "        "
            }
        }
        Rectangle{
            id: monitor_memory
            anchors.top: monitor_cpu.bottom
            width: parent.width
            height: 50
            color: '#00000000'
            Text {
                id: monitor_memory_text
                text: "memory: " + methods.getMemoryRate() +"%"
                anchors.topMargin: 20
                font.bold: Font.Bold
                leftPadding: 15
                font.pointSize: 10
                Text{
                    id: monitor_memory_graph
                    anchors.top: monitor_memory_text.bottom
                    leftPadding: 15
                    text: "        "
                }
            }
        }
    }
    Rectangle{
        id: weather
        color: root.itemBackgroundColor
        width: parent.width - 40
        height: 150
        radius: 30
        anchors.left: parent.left
        anchors.top: time.bottom
        anchors.topMargin: 35
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        Rectangle{
            id: weather_icon_temp
            height: 0.6*parent.height
            width: parent.width
            color: "#00000000"
            Text{
                id: weather_icon
                text:  "☁"
                font.pointSize: 50
                leftPadding: 20
            }
            Text{
                id: weather_temp
                text:  ""
                font.pointSize: 25
                anchors.left: weather_icon.right
                topPadding: 20
                leftPadding: 20

            }
        }
        Rectangle{
            id: weather_infos
            anchors.top: weather_icon_temp.bottom
            color: "#00000000"
            width: parent.width
            height: 0.4*parent.height
            Text{
                id: weather_description
                font.pointSize: 10
                leftPadding: 25
                text: "天气:"
            }
            Text{
                id: weather_max_temp
                font.pointSize: 10
                anchors.left: weather_description.right
                text: "最大温度:"
                leftPadding:50
            }

            Text{
                id: weather_wind_speed
                anchors.left: weather_max_temp.right
                font.pointSize: 10
                text: "风速:"
                leftPadding:50
            }
            Text{
                id: weather_city
                font.pointSize: 12
                anchors.top: weather_description.bottom
                text: ""
                leftPadding:20
                topPadding: 15
                font.bold: true
            }
            Text{
                id: weather_min_temp
                font.pointSize: 10
                text: "最小温度"
                anchors.top: weather_max_temp.bottom
                anchors.left: weather_max_temp.left
                leftPadding:50
                topPadding: 20
            }
            Text{
                id: weather_humidity
                font.pointSize: 10
                text: "湿度:"
                anchors.top: weather_wind_speed.bottom
                anchors.left: weather_wind_speed.left
                leftPadding:50
                topPadding: 20
            }

        }
    }

    Rectangle{
        id: dashboard
        color: root.itemBackgroundColor
        width: parent.width - 40
        height: 80
        radius: 30
        anchors.left: parent.left
        anchors.top: weather.bottom
        anchors.topMargin: 35
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        Rectangle{
            id: dashboard_day
            height: parent.height - 20
            width: 50
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 10
            anchors.leftMargin: 20
            color: "#FFFFFF"
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: Qt.formatDateTime(new Date(), "dd");
                font.pointSize: 15
            }
        }

        Progress{
            id: cpu_progress
            width: 50
            height: parent.height -20
            anchors.top: parent.top
            anchors.left: dashboard_day.right
            anchors.topMargin: 20
            anchors.leftMargin: 20
            value: 50
            fontPx: 10
            speed: 0.5

        }

        Progress{
            id: memory_progress
            width: 50
            height: parent.height -20
            waveColor: "#FF575D"
            anchors.top: parent.top
            anchors.left: cpu_progress.right
            anchors.topMargin: 20
            anchors.leftMargin: 20
            value: 50
            fontPx: 10
            speed: 0.5
        }


    }

    function getCurrentTime(){
        return Qt.formatDateTime(new Date(), "hh:mm");

    }
    function getGraph(num){
        let graphs = ["▁","▂","▃","▄","▅","▅","▇","█"]
        if(num<12.5)
            return graphs[0]
        if(num<25)
            return graphs[1]
        if(num<37.5)
            return graphs[2]
        if(num<50)
            return graphs[3]
        if(num<62.5)
            return graphs[4]
        if(num<75)
            return graphs[5]
        if(num<87.5)
            return graphs[6]
        if(num<=100)
            return graphs[7]
    }
    function getweather(){
        let xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
                console.log('HEADERS_RECEIVED')
            } else if(xhr.readyState === XMLHttpRequest.DONE) {
                console.log('GET weather DONE')
                let object = JSON.parse(xhr.responseText);
                console.log(object.main.temp_max)
                weather_temp.text = object.main.temp+"°c"
                weather_description.text = ""+object.weather[0].description
                weather_max_temp.text =  "最大温度:"+object.main.temp_max
                weather_min_temp.text =  "最小温度:"+object.main.temp_min
                weather_wind_speed.text = "风速:"+object.wind.speed
                weather_city.text = ""+object.name
                weather_humidity.text = "湿度:"+object.main.humidity
            }
        }
        xhr.open("GET", "http://api.openweathermap.org/data/2.5/weather?q=huizhou&appid=2be809d34a2cb2fd8e356f2b9bfd710d&lang=zh_cn&units=metric");
        xhr.send();

    }
    property real cpuUsage: 0
    property real memoryUsage: 0
    Timer{
        id: timer_1s
        interval: 1000 //间隔(单位毫秒):1000毫秒=1秒
        repeat: true //重复
        onTriggered:{
            getMonitorInfo()

            time_text.text = getCurrentTime();
            monitor_cpu_text.text =  "cpu: " + cpuUsage +"%"
            monitor_memory_text.text = "memory: " + memoryUsage +"%"

            monitor_cpu_graph.text+= getGraph(cpuUsage)
            monitor_memory_graph.text+= getGraph(memoryUsage)
            let temp = monitor_cpu_graph.text.split('')
            temp.shift()
            monitor_cpu_graph.text = temp.join('')
            temp = monitor_memory_graph.text.split('')
            temp.shift()
            monitor_memory_graph.text = temp.join('')

            cpu_progress.value = cpuUsage
            memory_progress.value = memoryUsage
        }
    }
    function getMonitorInfo(){
        let infos = methods.getInfos()
        cpuUsage = (infos.cpuUsage).toFixed(2);
        memoryUsage =  infos.memoryUsage
    }


    Component.onCompleted: {
        timer_1s.start();
        getweather();
    }
}

