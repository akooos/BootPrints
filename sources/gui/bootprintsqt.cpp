#include "bootprintsqt.h"

#include <dispatcherqt.h>
#include <QIcon>
#include <iostream>
#include <QDesktopWidget>
#include <QMessageBox>
#include <exception.h>

 char  *ize[] = {"lalala"};
const int count1 = 1;

BootPrintsQt::BootPrintsQt(
        int argc,
        char *argv[]
)  : BootPrints::Core(nullptr),


    mainWindow()

{


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

    mainWindow.setWindowIcon(QIcon::fromTheme(":/appMainIcon",QIcon::fromTheme("applications-multimedia")));

}

DispatcherSPtr BootPrintsQt::createDispatcher(BootPrints::Interfaces::Plugin *plugin, const QJsonObject &metaData)
{
   return QSharedPointer<Dispatcher>( new DispatcherQt(plugin,metaData) );
}

void BootPrintsQt::initializeDispatcher(DispatcherSPtr dispatcher)
{
    Core::initializeDispatcher(dispatcher);

}
void BootPrintsQt::loadPlugins()
{
   DEBUG_MSG("Loading plugins: started")

   QDir pluginsDir(qApp->applicationDirPath());
   pluginsDir.cd("plugins");
   DEBUG_MSG("Loading plugins from:" << pluginsDir.absolutePath() )
   try
   {
     QStringList lsProblems = addPlugins(pluginsDir);
     initPlugins();
   } catch(BootPrints::Exception exception)
   {
     QMessageBox::critical(
                 0,
                 QObject::tr(gui_app_name),
                 exception.toString()
     );

      std::cout << std::endl;
   }

  DEBUG_MSG("Loading plugins: finished")
}

void BootPrintsQt::loadConfig()
{
    DEBUG_MSG("Loading configuration: started")
    //detect first run
    if ( !config.previousStartupDateTime.exists() )
    {
        setDefaultConfig();
    }
    QDateTime startupTime = config.previousStartupDateTime;
    QDateTime shutdownTime = config.previousShutdownDateTime;
    //previous run was stopped, or bad shutdown(fail)
    if ( shutdownTime.isValid()
             &&
         startupTime.isValid()
             &&
         shutdownTime < startupTime
         )
    {
        //TODO: popup a message, whether we allowed to set the defaults
        setDefaultConfig();
    }
    DEBUG_MSG("Previous start time" << startupTime.toString())
    DEBUG_MSG("Previous end time" << shutdownTime.toString())
    config.previousStartupDateTime = QDateTime::currentDateTime();
    mainWindow.restoreGeometry(config.geometry);
    mainWindow.restoreState(config.windowState);
    DEBUG_MSG("Loading configuration: finished")
}

void BootPrintsQt::saveConfig()
{
    DEBUG_MSG("Saving configuration: started")
    config.geometry = mainWindow.saveGeometry();
    config.windowState = mainWindow.saveState();
    DEBUG_MSG("Saving configuration: finished")
}

void BootPrintsQt::setDefaultConfig()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    auto screen_height = rec.height();
    auto screen_width = rec.width();
    //position to middle, and occupie 80% of the screen
    const float percentOccupied = 0.8f;
    const int window_height = screen_height * percentOccupied;
    const int window_width = screen_width * percentOccupied;
    const int top = ( screen_height / 2 ) - ( window_height / 2 );
    const int left = ( screen_width / 2 ) - ( window_width / 2 );
    mainWindow.setGeometry(left,top,window_width,window_height);
    mainWindow.setWindowState(Qt::WindowActive);
}

int BootPrintsQt::execute()
{
    return 0;
}

void BootPrintsQt::quit(int exitcode)
{
    saveConfig();
    config.previousShutdownDateTime = QDateTime::currentDateTime();

    disposePlugins();

    QApplication::exit(exitcode);
}


