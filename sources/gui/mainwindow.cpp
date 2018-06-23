
#include "mainwindow.h"
#include <bootprintsqt.h>

#include <QCloseEvent>

MainWindow::MainWindow(
        QWidget *parent
) : QMainWindow(parent)

{     
    SCOPE_SENTINEL
    ui.setupUi(this);
    setWindowIcon(QIcon::fromTheme(":/appMainIcon",QIcon::fromTheme("applications-multimedia")).pixmap(QSize(256,256)));
}

MainWindow::~MainWindow()
{
  SCOPE_SENTINEL
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SCOPE_SENTINEL
    event->accept();
    BootPrintsQt::instance()->quit();
}



