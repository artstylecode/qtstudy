#include "gotocelldialog.h"
#include "ui_gotocelldialog.h"
#include <QPushButton>
GoToCellDialog::GoToCellDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoToCellDialog)
{
    ui->setupUi(this);
    QPushButton * okbutton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okbutton->setEnabled(false);
    //添加输入框验证正则表达式
    QRegExp reg("[A-Za-z][1-9][0-9],{0,2}");
    ui->lineEdit->setValidator(new QRegExpValidator(reg,this));
    //信号链接信号
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableGoToButton(QString)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}
void GoToCellDialog::enableGoToButton(QString str)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->lineEdit->hasAcceptableInput());
}
void GoToCellDialog::reject()
{
    emit cancelCliecked();
    close();
}
void GoToCellDialog::accept()
{
 QString cellText = ui->lineEdit->text();
 emit goToClicked(cellText);
 close();
}
GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}
