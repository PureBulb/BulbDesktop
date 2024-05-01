#ifndef IPENDANTPLUGIN_H
#define IPENDANTPLUGIN_H

#include <stdint.h>
#include <QWidget>
#include <QList>
#include <QPluginMetaData>
#include <QDialog>
#include <QDebug>
class BasePendantWidget:public QWidget
{
    Q_OBJECT
protected:
    QWidget* _parent;
    uint64_t id;
public:
    BasePendantWidget(QWidget* parent):QWidget(parent),_parent(parent){};
    virtual uint64_t getId(){return 0;};
    void editMode(){
        setWindowFlags(windowFlags() & (~Qt::FramelessWindowHint));
        QWidget::setParent(nullptr);
        show();
    }
    void closeEditMode(){
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        QWidget::setParent(_parent);
        show();
    }
    void setParent(QWidget* parent){
        _parent = parent;
        QWidget::setParent(_parent);
    };
};

class IPendantPlugin: public QObject
{
    Q_OBJECT
protected:
    QList<BasePendantWidget*> widgets; //一个挂件多个实例，实例放在这里
    bool isEditMode = false;
public:
    IPendantPlugin(){};

    virtual void loaded() {} //在这里通读取配置
    virtual void unloaded() {foreach(auto widget,widgets){widget->deleteLater();}} //卸载时要清除资源
    virtual void activated() {} // 在这里将配置中的挂件全部初始化
    virtual void finished() {}
    void startEditMode(){
        isEditMode = true;
        foreach (auto widget, widgets) {

            widget->editMode();
        }
    }
    void endEditMode(){
        isEditMode = false;
        foreach (auto widget, widgets) {
            widget->closeEditMode();
        }
    }
    virtual BasePendantWidget* createNewWidget(int x,int y,int w,int h){return nullptr;}; // 返回已经初始化的挂件让插件管理器显示
signals:
    // log 信号，在本例子中信号由LogDispacher发出 该接口继承者接受处理并发送给插件管理类处理
    void reportError(QString module, QString msg);
    void reportInfo(QString module, QString msg);
    void reportWarring(QString module, QString msg);
    void reportDebug(QString module, QString msg);

};
QT_BEGIN_NAMESPACE
#define PLUGIN_IID "org.qt-project.Qt.IPendantPlugin"
Q_DECLARE_INTERFACE(IPendantPlugin,PLUGIN_IID);
QT_END_NAMESPACE
#endif // IPENDANTPLUGIN_H
