
#include "mainwindow.h"

#include <QCloseEvent>

MainWindow::MainWindow(
        QWidget *parent
) : QMainWindow(parent)

{     
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}



