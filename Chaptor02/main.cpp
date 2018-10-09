#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include "gotocelldialog.h"
#include "finddialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GoToCellDialog  w;
    w.show();

    return app.exec();
}
