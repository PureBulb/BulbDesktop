#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{
    connect(getContext(),&Context::settingsChanged,this,&BaseWidget::onSettingsChanged);
}

BaseWidget::~BaseWidget()
{

}

Context *BaseWidget::getContext()
{
    return Context::getInstance();
}


