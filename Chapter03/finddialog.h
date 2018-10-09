#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>

namespace Ui {
class Finddialog;
}

class Finddialog : public QWidget
{
    Q_OBJECT
private slots:
    void enableFindButton(QString);
    void findTextClicked();
public:
    explicit Finddialog(QWidget *parent = 0);
    ~Finddialog();
signals:
    void findNext(QString &str, Qt::CaseSensitivity cs);
    void findPrevious(QString &str, Qt::CaseSensitivity cs);
private:
    Ui::Finddialog *ui;
};

#endif // FINDDIALOG_H
