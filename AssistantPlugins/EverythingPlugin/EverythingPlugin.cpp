#include "genericplugin.h"

GenericPlugin::GenericPlugin(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *GenericPlugin::create(const QString &name, const QString &spec)
{
    static_assert(false, "You need to implement this function");
}
