#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <ui_mainwindow.h>
#include "common.h"
#include "config.h"
#include "uiplugin.h"


class MainWindow : public QMainWindow, public UIPlugin
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual const QIcon & appIcon() const;
    virtual const QActionPtr actionClose() const;

private:    
    Ui::MainWindow  ui;

    QIcon   iconAppMain;
    QActionPtr aClose;

    QList<QAction> lsGeneralActions;

    void createTrayIcon();
    void createActions();
private slots:
    void onActionClose(bool);

};

#endif // MAINWINDOW_H
