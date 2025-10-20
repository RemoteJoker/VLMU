import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 350
    title: "Software Launcher"
    flags: Qt.FramelessWindowHint
    color: "#1e1e1e"
    property string selectedPath: ""
    property string selectedVersion: ""
    property int currentStep: 0
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
                    // 版本信息
                    Text {
                        id: versionText
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: selectedVersion ? "版本: " + selectedVersion : ""
                        color: "#4CAF50"
                        font.pixelSize: 11
                        visible: selectedVersion !== ""
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
            text: "自动启动管理器"
            color: "#888888"
            font.pixelSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    // 自动启动定时器
    Timer {
        id: autoLaunchTimer
        interval: 100
        onTriggered: startAutoLaunchProcess()
    }
    // 步骤执行定时器
    Timer {
        id: stepTimer
        interval: 800
        onTriggered: executeNextStep()
    }
    // 退出定时器
    Timer {
        id: exitTimer
        interval: 1000
        onTriggered: Qt.quit()
    }
    // 获取步骤标题
    function getStepTitle(step) {
        switch(step) {
            case 0: return "正在初始化..."
            case 1: return "读取配置..."
            case 2: return "分析版本..."
            case 3: return "启动程序..."
            case 4: return "启动完成"
            default: return "处理中..."
        }
    }
    // 获取进度宽度
    function getProgressWidth(step) {
        var totalSteps = 4;
        return progressBarBackground.width * (step / totalSteps);
    }
    // 开始自动启动流程
    function startAutoLaunchProcess() {
        console.log("开始自动启动流程")
        currentStep = 1
        g_load_service.readDatabaseConfig()
        stepTimer.start()
        // 新增：打印拼接后的路径（调试用）
        console.log("拼接后的启动路径:", g_load_service.geadDatabaseConfig())
    }
    // 执行下一步
    function executeNextStep() {
        console.log("执行步骤:", currentStep)
        if (currentStep === 1) {
            // 步骤1: 读取配置完成，分析版本
            currentStep = 2
            selectedPath = g_load_service.geadDatabaseConfig()
            selectedVersion = g_load_service.getHighestVersion()
            stepTimer.interval = 600
            stepTimer.start()

        } else if (currentStep === 2) {
            // 步骤2: 启动程序（修改：调用无参 launchProgram，后端自动处理重试）
            currentStep = 3
            if (g_load_service.geadDatabaseConfig() || g_load_service.getOldVersionPath()) {
                g_load_service.launchProgram() // 无需传参，后端内部重试
                stepTimer.interval = 800
                stepTimer.start()
            } else {
                showErrorState("未找到任何可用版本路径")
            }
        } else if (currentStep === 3) {
            // 步骤3: 完成并退出
            currentStep = 4
            loadingAnimation.stop()
            exitTimer.start()
        }
    }
    // 显示错误状态
    function showErrorState(errorMsg) {
        mainStatusText.text = "启动失败"
        mainStatusText.color = "#e74c3c"
        detailText.text = errorMsg
        detailText.color = "#e74c3c"
        loadingAnimation.stop()
        // 3秒后自动退出
        errorExitTimer.start()
    }
    // 错误退出定时器
    Timer {
        id: errorExitTimer
        interval: 3000
        onTriggered: Qt.quit()
    }
    // 初始化
    Component.onCompleted: {
        console.log("版本自动启动器启动")
        autoLaunchTimer.start()
    }
    // 连接后端状态消息变化
    Connections {
        target: g_load_service
        onStatusMessageChanged: {
            detailText.text = g_load_service.statusMessage
        }
    }
}
