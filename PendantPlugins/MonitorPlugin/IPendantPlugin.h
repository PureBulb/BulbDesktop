#ifndef IPENDANTPLUGIN_H
#define IPENDANTPLUGIN_H

#include <stdint.h>
#include <QWidget>
#include <QList>
#include <QMoveEvent>
#include <QScreen>
#include <QPluginMetaData>
#include <QDialog>
#include <QDebug>
#include <QEvent>
#include <QImage>
class BasePendantWidget:public QWidget
{
    Q_OBJECT
protected:
    uint64_t id;
    QRect globalRect;
    QRect relativeRect;
    bool isEditMode;
    bool m_isClose;
public:
    BasePendantWidget(QWidget* parent):QWidget{parent},globalRect{this->rect()},relativeRect{this->rect()},isEditMode{false},m_isClose{false}{};
    virtual uint64_t getId(){return id;};
    virtual void setId(uint64_t _id){id = _id;};

    void editMode(){
        isEditMode = true;

        setWindowFlags(windowFlags() & (~Qt::FramelessWindowHint));
        setParent(nullptr);
        if(!m_isClose)
            show();
        else
            hide();
    }
    void closeEditMode(const QVector<QWidget*>& wallpapers){
        isEditMode = false;
        setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
        setParent(findBestParent(wallpapers));
        if(!m_isClose)
            show();
        else
            hide();
    }
    void setParent(QWidget* parent){
        if(isEditMode){
            raise();
            show();
            move(globalRect.x(),globalRect.y());
            QWidget::setParent(parent);
        }
        else{
            QWidget::setParent(parent);
            //raise();
            show();
            move(relativeRect.x(),relativeRect.y());
        }

    };
    bool event(QEvent *e) override{
        switch(e->type()){
        case QEvent::Move:{ // 创建窗口时最好能触发move事件
            if(isEditMode){
                QRect screenGeometry = screen()->geometry();
                QPoint pos = dynamic_cast<QMoveEvent*>(e)->pos();
                globalRect.moveTo(pos);
                relativeRect.moveTo(pos.x()-screenGeometry.x(),pos.y()-screenGeometry.y());
            }
        }
        case QEvent::Resize:
            if(isEditMode){
                relativeRect.setWidth(geometry().width());
                relativeRect.setHeight(geometry().height());
                globalRect.setWidth(geometry().width());
                globalRect.setHeight(geometry().height());
                emit changeWidget(id,geometry());
            }
            break;
        case QEvent::Close:
            m_isClose = true;
            emit closeWidget(id);
            break;
        default:
            break;
        }
        return QWidget::event(e);
    };
    QWidget* findBestParent(const QVector<QWidget*>& wallpapers){
        for(auto wallpaper : wallpapers){
            auto screenRect = wallpaper->screen()->geometry();
            if(
                screenRect.x()<=geometry().x()   &&
                screenRect.y()<=geometry().y()&&
                (screenRect.x()+screenRect.width())>=(geometry().x()+geometry().width()) &&
                (screenRect.y()+screenRect.height())>=(geometry().y()+geometry().height())
                ){
                return wallpaper;
            }
        }
        return nullptr;
    }
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
    void endEditMode(const QVector<QWidget*>& wallpapers){
        isEditMode = false;
        foreach (auto widget, widgets) {
            widget->closeEditMode(wallpapers);
        }
    }
    // 返回已经初始化的挂件让插件管理器显示
    // id建议使用64位时间戳避免冲突
    virtual BasePendantWidget* createNewWidget(int x,int y,int w,int h,uint64_t id=0){return nullptr;};
    virtual QImage getIcon(){return QImage();};
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
