#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "config.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:    
    Ui::MainWindow  *ui;
    QSystemTrayIcon *systemTrayIcon;
    QIcon            iconAppMain;

    QAction   *actionClose;

    void createTrayIcon();
    void createActions();
private slots:
    void onActionClose(bool);
    void onSystemTrayActivated(QSystemTrayIcon::ActivationReason);
};

#endif // MAINWINDOW_H
