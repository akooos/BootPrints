#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>

class TrayIcon : public QObject
{
    Q_OBJECT
        //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.EchoInterface" FILE "echoplugin.json")
        //Q_INTERFACES(EchoInterface)

public:
    TrayIcon();
};



#endif // TRAYICON_H
