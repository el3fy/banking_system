
#include <QApplication>
#include <QScopedPointer>
#include "view.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    View view;

    return a.exec();
}
