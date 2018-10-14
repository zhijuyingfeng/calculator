#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{

    QApplication cal(argc, argv);
    MainWindow w;
    w.show();
    return cal.exec();
}
