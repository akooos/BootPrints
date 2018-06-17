#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>

#include <config.h>
#include <plugin.h>

class UIInternal;

using namespace BootPrints::Interfaces;

class TrayIcon : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "trayicon.json")
    Q_INTERFACES( BootPrints::Interfaces::Plugin )
    UIInternal *ui;
    QMenu menu;
    QSystemTrayIcon systemTrayIcon;
    QAction actionClose;

public:
    TrayIcon(QObject *parent = 0);
    void init(BootPrints::Interfaces::Internal *core) override;
    void dispose() override;
private slots:
    void onSystemTrayActivated(QSystemTrayIcon::ActivationReason);
};

#endif // TRAYICON_H