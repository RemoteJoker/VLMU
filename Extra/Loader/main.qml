import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 350
    title: "Software Launcher"
    flags: Qt.FramelessWindowHint
    color: "#1e1e1e"
    property int currentStep: 0 //启动步骤
    property int currentFlag: 0 //启动成功与否的标志
    // 主内容区域
    Rectangle {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: messageArea.top
            margins: 10
        }
        color: "transparent"
        Column {
            anchors.centerIn: parent
            spacing: 25
            width: parent.width * 0.8
            // Logo/图片显示
            Image {
                id: displayImage
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80
                height: 80
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Resource/pic/back.png"
                mipmap: true
                // 旋转加载动画
                RotationAnimation on rotation {
                    id: loadingAnimation
                    from: 0
                    to: 360
                    duration: 1500
                    loops: Animation.Infinite
                    running: true
                }
            }
            // 状态显示区域
            Rectangle {
                width: parent.width
                height: 120
                color: "transparent"
                Column {
                    anchors.centerIn: parent
                    spacing: 15
                    width: parent.width
                    // 主状态文本
                    Text {
                        id: mainStatusText
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: getStepTitle(currentStep)
                        color: "white"
                        font.pixelSize: 16
                        font.bold: true
                    }
                    // 详细状态文本
                    Text {
                        id: detailText
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: g_load_service.statusMessage
                        color: "#cccccc"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        width: parent.width
                        wrapMode: Text.Wrap
                    }
                    // 进度条
                    Rectangle {
                        id: progressBarBackground
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        height: 4
                        radius: 2
                        color: "#333333"
                        Rectangle {
                            id: progressBar
                            width: getProgressWidth(currentStep)
                            height: parent.height
                            radius: parent.radius
                            color: "#4CAF50"
                            Behavior on width {
                                NumberAnimation { duration: 300 }
                            }
                        }
                    }
                }
            }
        }
    }
    // 底部消息显示区域
    Rectangle {
        id: messageArea
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 40
        color: "#2d2d2d"
        Text {
            anchors {
                fill: parent
                margins: 8
            }
            text: "启动器"
            color: "#888888"
            font.pixelSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    // 先在外部定义消息框
    MessageDialog {
        id: msgDialog
        title: "启动错误"
        icon: MessageDialog.Critical
        standardButtons: MessageDialog.Ok
        text: "启动失败，请联系维护人员\n" +
              "车型开发工程组-杨刚（yangg11@xiaopeng.com）\n" +
              "车型开发工程组-王晓飞（par-xiaofeiwa@wicresoft.com）"
        onAccepted: {
            Qt.quit()
        }
    }
    // 步骤执行定时器
    Timer {
        id: stepTimer
        interval: 800
        onTriggered: executeNextStep()
    }
    // 获取步骤标题
    function getStepTitle(step) {
        switch(step) {
            case 0: return "读取配置..."
            case 1: return "启动程序..."
            case 2: return "启动完成"
            default: return "处理中..."
        }
    }
    // 获取进度宽度
    function getProgressWidth(step) {
        var totalSteps = 2;
        return progressBarBackground.width * (step / totalSteps);
    }
    // 执行下一步
    function executeNextStep() {
        if (currentStep == 0) {
            // 读取配置
            currentStep = 1
            if(!g_load_service.initService()){
                msgDialog.open()
            }else{
                if (g_load_service.getCfgPath()) {
                    if(!g_load_service.launchProgram()){
                        currentFlag = 1
                    }
                    stepTimer.interval = 800
                    stepTimer.start()
                } else {
                    msgDialog.open()
                }
            }
        } else if (currentStep == 1) {
            // 步骤3: 完成并退出
            currentStep = 2
            loadingAnimation.stop()
            if(currentFlag == 1){
                //启动失败，打开
                msgDialog.open()
            }else{
                Qt.quit()
            }
        }
    }
    // 初始化
    Component.onCompleted: {
        stepTimer.start()
    }
    // 连接后端状态消息变化
    Connections {
        target: g_load_service
        onStatusMessageChanged: {
            detailText.text = g_load_service.statusMessage
        }
    }
}
