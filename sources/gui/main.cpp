#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DEBUG_MSG("Starting application.")
    Q_INIT_RESOURCE(icons);

    QApplication::setOrganizationName("Ak ooos");
    QApplication::setOrganizationDomain("Hungary");
    QApplication::setApplicationDisplayName("BootPrints");
    QApplication::setApplicationName("BootPrints");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setQuitOnLastWindowClosed(true);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
