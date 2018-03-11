
#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iconAppMain(QIcon(":/appMainIcon"))
{     
    setWindowIcon(iconAppMain);
    ui->setupUi(this);
    QString dbHost = Conf.dbHost;
    DEBUG_MSG(dbHost)
    Conf.dbHost = QString("Teszt");
    createActions();
    createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete systemTrayIcon;
    delete ui;
}

void MainWindow::createActions()
{
    actionClose = new QAction(tr("Close"));

    bool checker = QObject::connect(actionClose,SIGNAL(triggered(bool)),this,SLOT(onActionClose(bool)));

    Q_ASSERT(checker);

    Q_UNUSED(checker);
}
void MainWindow::createTrayIcon()
{
    QMenu *menu = new QMenu(this);
    menu->addAction(actionClose);

    ui->centralWidget->addAction(actionClose);

    systemTrayIcon = new QSystemTrayIcon(iconAppMain,this);
    systemTrayIcon->setContextMenu(menu);
    systemTrayIcon->show();

    bool checker = QObject::connect(systemTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(onSystemTrayActivated(QSystemTrayIcon::ActivationReason)));

    Q_ASSERT(checker);
}

void MainWindow::onActionClose(bool triggered)
{

    Q_UNUSED(triggered)

    QApplication::quit();

}

void MainWindow::onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            setVisible( !isVisible() );
            break;
        case QSystemTrayIcon::MiddleClick:
            break;
        default:
            ;
        }
}
