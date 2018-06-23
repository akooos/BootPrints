
#include "mainwindow.h"
#include <bootprintsqt.h>

#include <QCloseEvent>

MainWindow::MainWindow(
        QWidget *parent
) : QMainWindow(parent)

{     
    SCOPE_CHECKER
    ui.setupUi(this);
    setWindowIcon(QIcon::fromTheme(":/appMainIcon",QIcon::fromTheme("applications-multimedia")).pixmap(QSize(256,256)));
}

MainWindow::~MainWindow()
{
  SCOPE_CHECKER
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SCOPE_CHECKER
    event->accept();
    BootPrintsQt::instance()->quit();
}



