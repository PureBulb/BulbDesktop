QT += widgets quickwidgets quick

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logdispacher.cpp \
    monitorwidget.cpp \
    pendantplugin.cpp


HEADERS += \
    IPendantPlugin.h \
    logdispacher.h \
    monitorwidget.h \
    pendantplugin.h

DISTFILES += MonitorPlugin.json \
    dependence.ps1 \
    MonitorQml.qml

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

FORMS += \
    monitorwidget.ui
