#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



#include <ui_mainwindow.h>

class QCloseEvent;

class MainWindow : public QMainWindow
{
   Q_OBJECT

    Ui::MainWindow ui;

  protected:
    virtual void closeEvent(QCloseEvent *event) override;

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

};

#endif // MAINWINDOW_H
