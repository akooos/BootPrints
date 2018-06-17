#ifndef UICORE_H
#define UICORE_H


#include <common.h>

#include <core.h>

#include <config.h>
#include <singleton.h>


#include <mainwindow.h>

#include <QApplication>


namespace  {
    extern char const gui_app_name[] = "bootprints-qtui";
}


class BootPrintsQt : public BootPrints::Core, public Singleton<BootPrintsQt,int, char*[]>
{



    struct Config : BootPrints::Config<gui_app_name>
    {
       CONFIG_PROPERTY(QByteArray,geometry)
       CONFIG_PROPERTY(QByteArray,windowState)
       CONFIG_PROPERTY(QDateTime,previousStartupDateTime)
       CONFIG_PROPERTY(QDateTime,previousShutdownDateTime)
    } config;

    void createTrayIcon();
    void createActions();
    void loadPlugins();
    void loadConfig();
    void saveConfig();
    void setDefaultConfig();


    MainWindow mainWindow;

    friend class DispatcherQt;




  public:
explicit BootPrintsQt(int argc, char *argv[]);
    int execute();
    void quit(int exitcode = 0);


  protected:


    virtual DispatcherSPtr createDispatcher(
            BootPrints::Interfaces::Plugin *plugin,
            const QJsonObject &metaData
    );

    virtual void initializeDispatcher(
            DispatcherSPtr dispatcher
    );


};

#endif // UICORE_H
