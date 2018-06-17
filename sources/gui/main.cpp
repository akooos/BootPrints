#include "bootprintsqt.h"

int main(int argc, char *argv[])
{
    QApplication application(argc,argv);
    BootPrintsQt::create(argc,argv).execute();
    return application.exec();
}
