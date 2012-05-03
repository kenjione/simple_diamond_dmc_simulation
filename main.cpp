#include <QtGui/QApplication>
#define NDEBUG // убрать в релизной версии
#include <assert.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    return a.exec();
}
