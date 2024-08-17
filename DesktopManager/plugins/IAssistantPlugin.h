#ifndef IASSISTANTPLUGIN_H
#define IASSISTANTPLUGIN_H

#include <QIcon>
#include <QObject>
#include <QString>
#include <QList>
#include <QPluginMetaData>


enum ResultType{file,folder,program};

struct QueryResult{
public:

    QString getTitle() {return  title;};
    void setTitle(const QString &value){ title = value;};

    QString getDescription() {return description;};
    void setDescription(const QString &value){description = value;};

    ResultType getType() {return type;};
    void setType(const ResultType &value){type = value;};

    std::function<void ()> getItemClick() {return itemClick;};
    void setItemClick(const std::function<void (QueryResult)> value){
        itemClick = std::bind(value,*this);
    };

    std::function<void ()> getBtn1Click() {return btn1Click;};
    void setBtn1Click(const std::function<void (QueryResult)> value){
        btn1Click = std::bind(value,*this);
    };

    std::function<void ()> getBtn2Click() {return btn2Click;};
    void setBtn2Click(const std::function<void (QueryResult)> value){
        btn2Click = std::bind(value,*this);
    };



    std::function<QIcon ()> getIconFunc() {return iconFunc;};
    void setIconFunc(const std::function<QIcon(QueryResult)> &value){
        iconFunc = std::bind(value,*this);
    };
    void setLeftBtnName(QString name){
        leftBtnName = name;
    }
    void setRightBtnName(QString name){
        rightBtnName = name;
    }
    QString getLeftBtnName(){
        return leftBtnName;
    }
    QString getRightBtnName(){
        return rightBtnName;
    }
private:

    QString title;
    QString description;
    QString leftBtnName;
    QString rightBtnName;

    ResultType type;
    std::function<void()> itemClick;    //when you are setting it please use IAssistantPlugin::returnItemClickFunc to get the call function
    std::function<void()> btn1Click;    //when you are setting it please use IAssistantPlugin::returnBtn1ClickFunc to get the call function
    std::function<void()> btn2Click;    //when you are setting it please use IAssistantPlugin::returnBtn2ClickFunc to get the call function
    std::function<QIcon()> iconFunc;    //when you are setting it please use IAssistantPlugin::returnBtn2ClickFunc to get the call function
};

class IAssistantPlugin {
    friend struct QueryResult;
protected:
    uint8_t pluginProperty; // 0-50 is the highest level, only system plugin can be
    virtual void onItemClick(QueryResult){};
    virtual void onBtn1Click(QueryResult){};
    virtual void onBtn2Click(QueryResult){};
    virtual QIcon getIconFunc(QueryResult){ return QIcon();};

    virtual std::function<void (QueryResult)> getOnItemClickFunc(){
        return std::bind(&IAssistantPlugin::onItemClick,this,std::placeholders::_1);
    };
    virtual std::function<void (QueryResult)> getOnBtn1ClickFunc(){
        return std::bind(&IAssistantPlugin::onBtn1Click,this,std::placeholders::_1);
    };
    virtual std::function<void (QueryResult)> getOnBtn2ClickFunc(){
        return std::bind(&IAssistantPlugin::onBtn2Click,this,std::placeholders::_1);
    };
    virtual std::function< QIcon(QueryResult)> getGetIconFunc(){
        return std::bind(&IAssistantPlugin::getIconFunc,this,std::placeholders::_1);
    };
public:
    virtual void loaded() = 0;
    virtual void unload() = 0;
    /*
     * 参数：
     *  queryStr:查询字符串
     *  result：结果集合
     * 返回：
     *  true: 本插件数据+其他插件数据
     *  false： 优先级低（数字大）的插件将不再进行
    */
    virtual bool query(QString queryStr,QList<QueryResult>& result) = 0;
    virtual uint8_t getPluginProperty(){return this->pluginProperty;};
    virtual ~IAssistantPlugin(){}

    //TODO: context setting manager link
};

/*
 * json mate demo
{
    "plugin-name" : "xxx",
    "dependencies" : [ ],
    "type" : "assistant"
}
*/

QT_BEGIN_NAMESPACE
#define PLUGIN_IID "org.qt-project.Qt.IAssistantPlugin"
Q_DECLARE_INTERFACE(IAssistantPlugin,PLUGIN_IID);
QT_END_NAMESPACE
#endif // IASSISTANTPLUGIN_H

