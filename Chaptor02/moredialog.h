#ifndef MOREDIALOG_H
#define MOREDIALOG_H

#include <QDialog>

namespace Ui {
class MoreDialog;
}

class MoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoreDialog(QWidget *parent = 0);
    ~MoreDialog();

private:
    Ui::MoreDialog *ui;
};

#endif // MOREDIALOG_H
