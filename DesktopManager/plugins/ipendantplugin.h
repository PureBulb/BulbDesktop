#ifndef IPENDANTPLUGIN_H
#define IPENDANTPLUGIN_H

#include <stdint.h>
#include <QWidget>
#include <QList>
#include <QPluginMetaData>
#include <QDialog>
#include <QDebug>
#include <QEvent>
class BasePendantWidget:public QWidget
{
    Q_OBJECT
protected:
    QWidget* _parent;
    uint64_t id;
public:
    BasePendantWidget(QWidget* parent):QWidget(parent),_parent(parent){};
    virtual uint64_t getId(){return id;};
    virtual void setId(uint64_t _id){id = _id;};
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
    bool event(QEvent *e) override{
        if(e->type() == QEvent::Resize || e->type() == QEvent::Move){
            emit changeWidget(id,geometry());
        }
        if(e->type() == QEvent::Close){
            emit closeWidget(id);

        }
    };
signals:
    void changeWidget(uint64_t id,QRect geometry);
    void closeWidget(uint64_t id);
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
    // 返回已经初始化的挂件让插件管理器显示
    // id建议使用64位时间戳避免冲突
    virtual BasePendantWidget* createNewWidget(int x,int y,int w,int h,uint64_t id=0){return nullptr;};
signals:
    // log 信号，在本例子中信号由LogDispacher发出 该接口继承者接受处理并发送给插件管理类处理
    void reportError(QString module, QString msg);
    void reportInfo(QString module, QString msg);
    void reportWarring(QString module, QString msg);
    void reportDebug(QString module, QString msg);

    void closePendant(uint64_t id);
    void changePendant(uint64_t id,QRect rect);


};
QT_BEGIN_NAMESPACE
#define PLUGIN_IID "org.qt-project.Qt.IPendantPlugin"
Q_DECLARE_INTERFACE(IPendantPlugin,PLUGIN_IID);
QT_END_NAMESPACE
#endif // IPENDANTPLUGIN_H
