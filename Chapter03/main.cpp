#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen();
    splash ->setPixmap(QPixmap(":/tmg.jpg"));
    Qt::Alignment topRight = Qt::AlignTop | Qt::AlignRight;
    splash ->showMessage(QObject::tr("Setting up the main window!"), topRight, Qt::white);
    MainWindow w;
    splash ->showMessage(QObject::tr("load modules..."), topRight, Qt::white);

    w.show();
    splash ->finish(&w);
    delete splash;

    return a.exec();
}
