QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QTPLUGIN += qtaudio_windows \
            qsqlite
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Manager.cpp \
    SettingManager.cpp \
    components/assistantitem.cpp \
    components/trayiconmenu.cpp \
    # context.cpp \
    log.cpp \
    main.cpp \
    utils/WindAdapterV2.cpp \
    utils/hookthread.cpp \
    utils/pluginUtils/AssistantPluginUtils.cpp \
    utils/pluginUtils/BasePluginUtils.cpp \
    utils/pluginUtils/PendantPluginUtils.cpp \
    utils/pluginUtils/WallpaperPluginUtils.cpp \
    utils/safequeue.cpp \
    utils/threadbase.cpp \
    widgets/AssistantForm.cpp \
    widgets/SettingWidget.cpp

HEADERS += \
    Manager.h \
    SettingManager.h \
    components/assistantitem.h \
    components/trayiconmenu.h \
    # context.h \
    log.h \
    plugins/IAssistantPlugin.h \
    plugins/IWallpaperPlugin.h \
    plugins/IPendantPlugin.h \
    utils/AVConfig.h \
    utils/WindAdapterV2.h \
    utils/hookthread.h \
    utils/pluginUtils/AssistantPluginUtils.h \
    utils/pluginUtils/BasePluginUtils.h \
    utils/pluginUtils/PendantPluginUtils.h \
    utils/pluginUtils/WallpaperPluginUtils.h \
    utils/safequeue.h \
    utils/threadbase.h \
    utils/videoUtils/videoUtils.h\
    widgets/AssistantForm.h \
    widgets/SettingWidget.h

FORMS += \
    components/assistantitem.ui \
    components/trayiconmenu.ui \
    widgets/SettingWidget.ui \
    widgets/assistantform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
LIBS += -L$$PWD/../ffmpeg/lib
LIBS += -luser32 \
        -ladvapi32 \
        -lavcodec \
        -lavdevice \
        -lavfilter \
        -lavformat \
        -lavutil \
        -lswresample \
        -lswscale

INCLUDEPATH += $$PWD/../ffmpeg/include
DEPENDPATH += $$PWD/../ffmpeg/include
#5L2c6ICF77ya57qv55yf55qE55S154Gv5rOh

RESOURCES += \
    Resource.qrc


