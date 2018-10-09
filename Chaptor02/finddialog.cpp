#include "finddialog.h"
#include "ui_finddialog.h"
#include <QtGui>
Finddialog::Finddialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Finddialog)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this,SLOT(enableFindButton(QString)));
    connect(ui->findButton, SIGNAL(clicked(bool)), this, SLOT(findTextClicked()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this,SLOT(close()));


}

Finddialog::~Finddialog()
{
    delete ui;
}
void  Finddialog::findTextClicked()
{
    //搜索字符串
    QString str = ui->lineEdit->text();
    //获取大小写状态
    Qt::CaseSensitivity cs = ui->cb_MatchCase->isChecked()? Qt::CaseInsensitive :Qt::CaseSensitive;
    //根据向后搜索框进行向后或向前搜索
    if(ui->cb_isback->isChecked())
    {
        emit findPrevious(str, cs);
    }else
    {
        emit findNext(str, cs);
    }
}
void Finddialog::enableFindButton(QString str)
{
    ui->findButton->setEnabled(!str.isEmpty());
}
