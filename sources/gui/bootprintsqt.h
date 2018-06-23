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


class BootPrintsQt : public BootPrints::Core, public Singleton<BootPrintsQt>
{
    Q_OBJECT
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

    friend class DispatcherQt;

  public:
    explicit BootPrintsQt();
    virtual ~BootPrintsQt();

    MainWindow mainWindow;

    void quit(int exitcode = 0);
    void start();

    static int start(int argc, char *argv[])
    {
        SCOPE_CHECKER
        QApplication application(argc,argv);

        Q_INIT_RESOURCE(icons);

        DEBUG_MSG("Initialiazing BootPrints based on Qt." )
        DEBUG_MSG("Version"<< BootPrints::version)
        DEBUG_MSG("SCCS version" << BootPrints::sccs_version)
        DEBUG_MSG("Build date" << BootPrints::build_date << BootPrints::build_time)
        DEBUG_MSG("Compiler" << BootPrints::compiler)


        QApplication::setOrganizationName(BootPrints::org_name);
        QApplication::setOrganizationDomain(BootPrints::org_domain);
        QApplication::setApplicationDisplayName(BootPrints::app_name);
        QApplication::setApplicationName(BootPrints::app_name);
        QApplication::setApplicationVersion(BootPrints::version);
        QApplication::setQuitOnLastWindowClosed(true);
        auto instance = std::unique_ptr<BootPrintsQt>(BootPrintsQt::create());
        instance->start();
        return application.exec();
    }

 private slots:
    void onQuit(int errorcode);

   signals:
     void quitSignal(int errorcode = 0);
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
