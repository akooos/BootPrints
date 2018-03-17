#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DEBUG_MSG("Starting application.")
    Q_INIT_RESOURCE(icons);

    QApplication::setOrganizationName(STR(ORG_DOMAIN));
    QApplication::setOrganizationDomain(STR(ORG_DOMAIN));
    QApplication::setApplicationDisplayName(STR(APP_NAME));
    QApplication::setApplicationName(STR(APP_NAME));
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setQuitOnLastWindowClosed(true);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
