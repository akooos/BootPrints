#include "filesystemwatcher.h"


#include <QMessageBox>


FilesystemWatcher::FilesystemWatcher(QObject *parent):QObject(parent),ui(nullptr)
{
    systemTrayIcon.setContextMenu(&menu);
}

void FilesystemWatcher::init(CorePtr core, QHash<QString, BasePlugin *> deps )
{
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return;
    }

    auto it = deps.find("bootprints-qtui");
    if ( it == deps.end() )
    {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("Bootprints Qt UI does not run!"));
        return;
    }

    auto *ptr = *it;
    if ( !ptr )
    {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("Bootprints Qt UI does not run?! Empty pointer."));
        return;
    }

     ui = dynamic_cast<UIPlugin*> (ptr);

    if ( !ui )
    {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("Bootprints Qt UI does not run?! No proper pointer."));
        return;
    }

    QList<QAction*> actions;

    actions.append( ui->actionClose().data());
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

void FilesystemWatcher::dispose()
{
    ui = nullptr;
}
void FilesystemWatcher::onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason)
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
