#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DEBUG_MSG("Starting application.")
    Q_INIT_RESOURCE(icons);

    QApplication::setOrganizationName("Akooos");
    QApplication::setOrganizationDomain("Hungary");
    QApplication::setApplicationDisplayName("BootPrints");
    QApplication::setApplicationName("BootPrints");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setQuitOnLastWindowClosed(true);

    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }


    MainWindow w;
    w.show();

    return a.exec();
}
