#include <QCoreApplication>
#include "dbhandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DBHandler dbhandler;

    return a.exec();
}
