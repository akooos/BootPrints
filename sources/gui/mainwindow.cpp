
#include "mainwindow.h"

#include <iostream>
#include <QDesktopWidget>
#include <QMessageBox>
#include <exception.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    //iconAppMain(QIcon(":/appMainIcon")),
    iconAppMain(QIcon::fromTheme("applications-multimedia")),
    aClose(new QAction(QIcon::fromTheme("application-exit"), tr("Close")), &QObject::deleteLater ),
    core(BootPrints::Core())
{     
    setWindowIcon(iconAppMain);
    setWindowTitle(tr("Viewer"));
    ui.setupUi(this);

    DEBUG_MSG( "appversion "<< APP_VERSION)

    bool checker = QObject::connect(aClose.data(),SIGNAL(triggered(bool)),this,SLOT(onActionClose(bool)));

    Q_ASSERT(checker);

    Q_UNUSED(checker);

    loadConfig();
    loadPlugins();
}

MainWindow::~MainWindow()
{
}

const QIcon &MainWindow::appIcon() const
{
    return iconAppMain;
}

const QActionPtr MainWindow::actionClose() const
{
    return aClose;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveConfig();
    Config::instance().previousShutdownDateTime = QDateTime::currentDateTime();
    QMainWindow::closeEvent(event);
    //TODO rmeove this
    QApplication::quit();
}

void MainWindow::loadPlugins()
{
   DEBUG_MSG("Loading plugins: started")

   QDir pluginsDir(qApp->applicationDirPath());
   pluginsDir.cd("plugins");
   DEBUG_MSG("Loading plugins from:" << pluginsDir.absolutePath() )
  try{
       QStringList lsProblems = core.addPlugins(pluginsDir);
       core.addPlugin(GUI_APP_NAME,this);
       core.initPlugins();
   } catch(BootPrints::Exception exception)
   {
     QMessageBox::critical(0, QObject::tr(GUI_APP_NAME),
                             exception.toString()
                           );

      std::cout << std::endl;
   }

  DEBUG_MSG("Loading plugins: finished")
}

void MainWindow::loadConfig()
{
    DEBUG_MSG("Loading configuration: started")
    //detect first run
    if ( !Config::instance().previousStartupDateTime.exists() )
    {
        setDefaultConfig();
    }
    QDateTime startupTime = Config::instance().previousStartupDateTime;
    QDateTime shutdownTime = Config::instance().previousShutdownDateTime;
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
    Config::instance().previousStartupDateTime = QDateTime::currentDateTime();
    restoreGeometry(Config::instance().geometry);
    restoreState(Config::instance().windowState);
    DEBUG_MSG("Loading configuration: finished")
}

void MainWindow::saveConfig()
{
    DEBUG_MSG("Saving configuration: started")
    Config::instance().geometry = saveGeometry();
    Config::instance().windowState = saveState();
    DEBUG_MSG("Saving configuration: finished")
}

void MainWindow::setDefaultConfig()
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
    setGeometry(left,top,window_width,window_height);
    setWindowState(Qt::WindowActive);
}

void MainWindow::onActionClose(bool triggered)
{
    Q_UNUSED(triggered)
    QApplication::quit();
}


