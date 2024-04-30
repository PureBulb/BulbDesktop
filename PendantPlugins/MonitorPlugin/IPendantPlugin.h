#ifndef IPENDANTPLUGIN_H
#define IPENDANTPLUGIN_H

#include <stdint.h>
#include <QWidget>
#include <QList>
class BasePendantWidget:public QWidget
{
    Q_OBJECT
protected:
    uint64_t id;
public:
    virtual uint64_t getId();
};

class IPendantPlugin
{
protected:
    QList<BasePendantWidget*> widgets; //一个挂件多个实例，实例放在这里
public:
    IPendantPlugin();

    virtual void loaded() {} //在这里通读取配置
    virtual void unloaded() {foreach(auto widget,widgets){widget->deleteLater();}} //卸载时要清除资源
    virtual void activated() {} // 在这里将配置中的挂件全部初始化
    virtual void finished() {}

    virtual BasePendantWidget* createNewWidget(int x,int y,int w,int h); // 返回已经初始化的挂件让插件管理器显示
signals:

    // log 信号，在本例子中信号由LogDispacher发出 该接口继承者接受处理并发送给插件管理类处理
    void reportError(QString module, QString msg);
    void reportInfo(QString module, QString msg);
    void reportWarring(QString module, QString msg);
    void reportDebug(QString module, QString msg);

};

#endif // IPENDANTPLUGIN_H
