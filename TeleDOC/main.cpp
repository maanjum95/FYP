#include "mainwindow.h"
#include <QApplication>
#include <QtTest/QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(800, 480);
    w.show();

    return a.exec();
}


