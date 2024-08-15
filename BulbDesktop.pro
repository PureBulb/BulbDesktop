TEMPLATE = subdirs

SUBDIRS += \
    AssistantPlugins \
    DesktopManager \
    PendantPlugins \
    WallpaperPlugins


CONFIG += qt \
    qt

QT += widgets


DISTFILES += dependence.ps1
