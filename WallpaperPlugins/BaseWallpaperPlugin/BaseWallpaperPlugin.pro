QT       += core gui multimedia widgets
TEMPLATE = lib
CONFIG += plugin

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
    components/thumbnaillabel.cpp \
    settingsform.cpp \
    utils/audioUtils/AudioUtils.cpp \
    utils/audioUtils/IAudioPlayer.cpp \
    utils/logdispacher.cpp \
    utils/safequeue.cpp \
    utils/threadbase.cpp \
    utils/videoUtils/AVPacketQueue.cpp \
    utils/videoUtils/AudioDecoder.cpp \
    utils/videoUtils/AvFrameQueue.cpp \
    utils/videoUtils/DexmuxThread.cpp \
    utils/videoUtils/IDecoderBase.cpp \
    utils/videoUtils/displayworker.cpp \
    utils/videoUtils/syncclock.cpp \
    utils/videoUtils/videodecoder.cpp \
    utils/videoUtils/videoUtils.cpp\
    BaseWallpaperManager.cpp \
    BaseWallpaperPlugin.cpp \
    wallpaper.cpp

HEADERS += \
    common.h \
    components/thumbnaillabel.h \
    settingsform.h \
    utils/AVConfig.h \
    utils/audioUtils/AudioUtils.h \
    utils/audioUtils/IAudioPlayer.h \
    utils/logdispacher.h \
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
    BaseWallpaperPlugin.h \
    BaseWallpaperManager.h \
    wallpaper.h \
    IWallpaperPlugin.h
FORMS += \
    settingsform.ui \
    wallpaper.ui
DISTFILES += BaseWallpaperPlugin.json
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#libs
LIBS += -L$$PWD/../../ffmpeg/lib
LIBS += -luser32 \
        -ladvapi32 \
        -lavcodec \
        -lavdevice \
        -lavfilter \
        -lavformat \
        -lavutil \
        -lswresample \
        -lswscale
#INCLUDEPATH += $$PWD/../../DesktopManager/plugins
INCLUDEPATH += $$PWD/../../ffmpeg/include
#QMAKE_CXXFLAGS_RELEASE += -O        # Release -O
