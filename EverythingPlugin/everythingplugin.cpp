#include "everythingplugin.h"

EverythingPlugin::EverythingPlugin(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *EverythingPlugin::create(const QString &name, const QString &spec)
{
    static_assert(false, "You need to implement this function");
}
