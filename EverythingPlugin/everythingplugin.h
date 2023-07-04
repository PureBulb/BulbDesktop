#ifndef EVERYTHINGPLUGIN_H
#define EVERYTHINGPLUGIN_H

#include <QGenericPlugin>

class EverythingPlugin : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "EverythingPlugin.json")

public:
    explicit EverythingPlugin(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // EVERYTHINGPLUGIN_H
