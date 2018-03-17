
#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    iconAppMain(QIcon(":/appMainIcon")),
    aClose(new QAction(tr("Close")), &QObject::deleteLater )
{     
    setWindowIcon(iconAppMain);
    ui.setupUi(this);
    //QString dbHost = Conf.dbHost;
   // DEBUG_MSG(dbHost)
    //Conf.dbHost = QString("Teszt");
    DEBUG_MSG(APP_VERSION)
    DEBUG_MSG( PLUGIN_ID(kutya) )
    bool checker = QObject::connect(aClose.data(),SIGNAL(triggered(bool)),this,SLOT(onActionClose(bool)));

    Q_ASSERT(checker);

    Q_UNUSED(checker);
}

MainWindow::~MainWindow()
{
}

const QIcon &MainWindow::appIcon() const
{
    return iconAppMain;
}

const QActionPtr MainWindow::actionClose() const
{
    return aClose;
}

void MainWindow::onActionClose(bool triggered)
{

    Q_UNUSED(triggered)

    QApplication::quit();

}


