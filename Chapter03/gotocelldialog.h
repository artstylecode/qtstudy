#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QWidget>

namespace Ui {
class GoToCellDialog;
}

class GoToCellDialog : public QWidget
{
    Q_OBJECT
private slots:
    void accept();
    void reject();
    void enableGoToButton(QString str);
public:
    explicit GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();
signals:
    void goToClicked(const QString &str);
    void cancelCliecked();

private:
    Ui::GoToCellDialog *ui;
};

#endif // GOTOCELLDIALOG_H
