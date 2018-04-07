#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <ui_mainwindow.h>
#include "common.h"
#include "config.h"
#include "uiplugin.h"
#include <singleton.h>
#include <core.h>

namespace  {
    extern char const gui_app_name[] = "bootprints-qtui";
}

class MainWindow : public QMainWindow, public UIPlugin
{
   Q_OBJECT

  struct Config : BootPrints::Config<gui_app_name>, Singleton<Config>
  {
     CONFIG_PROPERTY(QByteArray,geometry)
     CONFIG_PROPERTY(QByteArray,windowState)
     CONFIG_PROPERTY(QDateTime,previousStartupDateTime)
     CONFIG_PROPERTY(QDateTime,previousShutdownDateTime)
  };

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
// --- U I  P l u g i n implementation ---
    virtual const QIcon & appIcon() const;
    virtual const QActionPtr actionClose() const;
//---------------------------------------

  protected:
    virtual void closeEvent(QCloseEvent *event) override;
  private:

    BootPrints::Core core;

    Ui::MainWindow  ui;

    QIcon   iconAppMain;
    QActionPtr aClose;

    QList<QAction> lsGeneralActions;

    void createTrayIcon();
    void createActions();
    void loadPlugins();
    void loadConfig();
    void saveConfig();
    void setDefaultConfig();
  private slots:
    void onActionClose(bool);

};

#endif // MAINWINDOW_H
