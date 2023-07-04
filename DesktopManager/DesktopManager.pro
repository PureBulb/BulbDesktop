QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/assistantitem.cpp \
    components/settingwidget.cpp \
    components/thumbnaillabel.cpp \
    components/trayiconmenu.cpp \
    context.cpp \
    log.cpp \
    main.cpp \
    plugins/IAssistantPlugin.cpp \
    utils/audioUtils/AudioUtils.cpp \
    utils/audioUtils/IAudioPlayer.cpp \
    utils/hookthread.cpp \
    utils/pluginUtils/assistantpluginutils.cpp \
    utils/pluginUtils/pluginutils.cpp \
    utils/safequeue.cpp \
    utils/threadbase.cpp \
    utils/videoUtils/AVFrameQueue.cpp \
    utils/videoUtils/AVPacketQueue.cpp \
    utils/videoUtils/AudioDecoder.cpp \
    utils/videoUtils/DexmuxThread.cpp \
    utils/videoUtils/IDecoderBase.cpp \
    utils/videoUtils/displayworker.cpp \
    utils/videoUtils/syncclock.cpp \
    utils/videoUtils/videodecoder.cpp \
    utils/windadapter.cpp \
    utils/videoUtils/videoUtils.cpp \
    widgets/AssistantForm.cpp \
    widgets/BaseWorkerform.cpp \
    widgets/mainwindow.cpp \
    widgets/workerform.cpp \
    widgets/BaseWidget.cpp

HEADERS += \
    components/assistantitem.h \
    components/settingwidget.h \
    components/thumbnaillabel.h \
    components/trayiconmenu.h \
    context.h \
    log.h \
    plugins/IAssistantPlugin.h \
    utils/AVConfig.h \
    utils/audioUtils/AudioUtils.h \
    utils/audioUtils/IAudioPlayer.h \
    utils/hookthread.h \
    utils/pluginUtils/assistantpluginutils.h \
    utils/pluginUtils/pluginutils.h \
    utils/safequeue.h \
    utils/threadbase.h \
    utils/videoUtils/AVPacketQueue.h \
    utils/videoUtils/AudioDecoder.h \
    utils/videoUtils/AvFrameQueue.h \
    utils/videoUtils/DexmuxThread.h \
    utils/videoUtils/IDecoderBase.h \
    utils/videoUtils/displayworker.h \
    utils/videoUtils/syncclock.h \
    utils/videoUtils/videodecoder.h \
    utils/windadapter.h \
    utils/videoUtils/videoUtils.h\
    widgets/AssistantForm.h \
    widgets/BaseWidget.h \
    widgets/BaseWorkerform.h \
    widgets/mainwindow.h \
    widgets/workerform.h

FORMS += \
    components/assistantitem.ui \
    components/settingwidget.ui \
    components/trayiconmenu.ui \
    widgets/assistantform.ui \
    widgets/mainwindow.ui \
    widgets/workerform.ui

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


#QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
#QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
#QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO


#QMAKE_CXXFLAGS_RELEASE -= -O
#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE -= -O3
#QMAKE_CXXFLAGS_RELEASE += -O0

#QMAKE_CXXFLAGS_DEBUG -= -O
#QMAKE_CXXFLAGS_DEBUG -= -O1
#QMAKE_CXXFLAGS_DEBUG -= -O2
#QMAKE_CXXFLAGS_DEBUG -= -O3
#QMAKE_CXXFLAGS_DEBUG += -O3
