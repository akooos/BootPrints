#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>

#include <config.h>
#include <plugin.h>
#include <uiplugin.h>

using namespace BootPrints::Interfaces;

class FilesystemWatcher : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "trayicon.json")
    Q_INTERFACES( BootPrints::Interfaces::Plugin )
    UIPlugin *ui;
    QMenu menu;
    QSystemTrayIcon systemTrayIcon;

public:
    FilesystemWatcher(QObject *parent = 0);
    void init( QHash<QString,BasePlugin*> deps ) override;
    void dispose() override;
private slots:
    void onSystemTrayActivated(QSystemTrayIcon::ActivationReason);
};

#endif // TRAYICON_H
