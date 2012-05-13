//#include <QtGui/QApplication>
#define NDEBUG // убрать в релизной версии
#include <assert.h>

#include "runner.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Runner *runner = new Runner;
    runner->run();
    //QApplication a(argc, argv);
    return 0; //a.exec();
}
