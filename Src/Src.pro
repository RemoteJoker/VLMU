QT  += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = VLMUInsight
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RC_ICONS = ico.ico
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/ThirdParty/include

contains(QT_ARCH, x86_64) {
    # 64位特定配置
win32{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    LIBS += -L$$PWD/ThirdParty/library/x64/windows -lmosquitto
    LIBS += -lwbemuuid -ldxgi -ladvapi32 -lpsapi
}
unix{
    icon.path = /home/xpeng/Project/Src/Src/Picture
    icon.files = ico.ico
    INSTALLS += icon
    LIBS += -L$$PWD/ThirdParty/library/x64/linux -lmosquitto
}
    DEFINES += ARCH_X64
}

SOURCES += \
    Global/globaldata.cpp \
    Global/globalset.cpp \
    Global/runlog.cpp \
    Model/ModelImpl/modelimpl.cpp \
    Model/coredumpmodel.cpp \
    Model/loginfomodel.cpp \
    Model/processmodel.cpp \
    Model/versionmodel.cpp \
    Service/ServiceImpl/serviceimpl.cpp \
    Service/controlservice.cpp \
    Service/dataservice.cpp \
    Service/netservice.cpp \
    Service/sqlservice.cpp \
    Service/updateservice.cpp \
    Utils/utils.cpp \
    View/ViewImpl/viewimpl.cpp \
    View/aboutview.cpp \
    View/commandview.cpp \
    View/dumpview.cpp \
    View/logview.cpp \
    View/processview.cpp \
    View/setview.cpp \
    View/versionview.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Global/globaldata.h \
    Global/globalset.h \
    Global/runlog.h \
    Model/ModelImpl/modelimpl.h \
    Model/coredumpmodel.h \
    Model/loginfomodel.h \
    Model/processmodel.h \
    Model/versionmodel.h \
    Service/ServiceImpl/serviceimpl.h \
    Service/controlservice.h \
    Service/dataservice.h \
    Service/netservice.h \
    Service/sqlservice.h \
    Service/updateservice.h \
    Utils/utils.h \
    View/ViewImpl/viewimpl.h \
    View/aboutview.h \
    View/commandview.h \
    View/dumpview.h \
    View/logview.h \
    View/processview.h \
    View/setview.h \
    View/versionview.h \
    mainwindow.h

FORMS += \
    View/aboutview.ui \
    View/commandview.ui \
    View/dumpview.ui \
    View/logview.ui \
    View/processview.ui \
    View/setview.ui \
    View/versionview.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
