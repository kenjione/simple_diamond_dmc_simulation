#include <QtGui/QApplication>
#include "mainwindow.h"

#define NDEBUG // убрать в релизной версии
#include <assert.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
