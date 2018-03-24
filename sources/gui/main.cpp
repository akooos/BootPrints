#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DEBUG_MSG("Starting application." << BootPrints::sccs_version )
    Q_INIT_RESOURCE(icons);

    QApplication::setOrganizationName(BootPrints::org_name);
    QApplication::setOrganizationDomain(BootPrints::org_domain);
    QApplication::setApplicationDisplayName(BootPrints::app_name);
    QApplication::setApplicationName(BootPrints::app_name);
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setQuitOnLastWindowClosed(true);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
