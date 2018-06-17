#include "trayicon.h"


#include <QMessageBox>

#include <internal.h>
#include <uiinternal.h>

TrayIcon::TrayIcon(
        QObject *parent
):QObject(parent),
    ui(nullptr),
    actionClose(QIcon::fromTheme("application-exit"), tr("Close"), this )
{
    systemTrayIcon.setContextMenu(&menu);
}

void TrayIcon::init(BootPrints::Interfaces::Internal *core)
{
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return;
    }

    if ( !core )
    {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("Bootprints Qt UI does not run?! Empty pointer."));
        return;
    }

     ui = dynamic_cast< UIInternal * > (core);

    if ( !ui )
    {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("Bootprints Qt UI does not run?! No proper pointer."));
        return;
    }

    QList<QAction*> actions;

    actions.append(&actionClose);

    menu.addActions(actions);
    systemTrayIcon.setIcon(ui->appIcon());
    systemTrayIcon.setVisible(true);

    bool checker = QObject::connect(
                &systemTrayIcon,
                SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this,
                SLOT(onSystemTrayActivated(QSystemTrayIcon::ActivationReason))
                );

    Q_ASSERT(checker);

    Q_UNUSED(checker);

}

void TrayIcon::dispose()
{
    ui = nullptr;
}
void TrayIcon::onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            //setVisible( !isVisible() );
            break;
        case QSystemTrayIcon::MiddleClick:
            break;
        default:
            ;
        }
}
