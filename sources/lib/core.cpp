
#include "core.h"
#include <interfaces/internal.h>
#include <QPluginLoader>
#include "share.h"
#include "mediaitem.h"
#include "plugin.h"
#include "internal.h"

using namespace BootPrints;


Core::Core( QObject *parent)
    : QObject(parent)
{

}

Core::~Core()
{

}

void Core::disposePlugins()
{
    //TODO dispose plugins as dependecies requires.
    for ( auto it = plugins.begin(); it != plugins.end();++it)
    {
        Interfaces::Plugin *bootprints_plugin = it.value()->getPluginPtr();
        if (bootprints_plugin)
        {
            DEBUG_MSG("Dispose plugin:" << it.key())
            bootprints_plugin->dispose();
        }else
        {
            DEBUG_MSG("Cannot dispose null ptr to plugin!")
        }
    }

    plugins.clear();
}

DispatcherSPtr Core::createDispatcher(Interfaces::Plugin *plugin, const QJsonObject & metaData)
{
    return  QSharedPointer<Dispatcher>( new Dispatcher(plugin,metaData) );
}

void Core::initializeDispatcher(DispatcherSPtr dispatcher)
{
    bool checker = QObject::connect(dispatcher.data(),SIGNAL(newShare(QUrl)),this,SLOT(onNewShare(QUrl)));

    Q_ASSERT(checker);

    checker = QObject::connect(dispatcher.data(),SIGNAL(newSubscriptionForShare(QString)),this,SLOT(onNewSubscribeForShare(QString)));

    Q_ASSERT(checker);

    Q_UNUSED(checker);
}

void Core::onNewShare(const QUrl &url)
{
    Dispatcher *dispatcher = qobject_cast<Dispatcher*> ( QObject::sender() );

    if ( !dispatcher )
    {
        DEBUG_MSG("dispatcher is NULL ptr!");
        return;
    }

    DEBUG_MSG("Share received" << url.toString())

    QList<Interfaces::Share *> ls = shareSubscriptions.values(dispatcher->getPluginPtr());
    for (Interfaces::Share * share : ls )
    {
        share->newShareReceived(url);
    }
}

void Core::onNewSubscribeForShare(const QString &pluginName)
{
    Dispatcher *subscriber = qobject_cast<Dispatcher*> ( QObject::sender() );
    Dispatcher *publisher = plugins.value(pluginName,nullptr).data();
    if ( !publisher )
    {
        DEBUG_MSG("Unknown subscription!");
        return;
    }
    if ( !subscriber )
    {
        DEBUG_MSG("Unknown subscriber!");
        return;
    }

    DEBUG_MSG("Subscriber" << subscriber->getMetaData().value("name").toString())
    DEBUG_MSG("Publisher" << publisher->getMetaData().value("name").toString())
    Interfaces::Share *share = dynamic_cast<Interfaces::Share*>(subscriber->getPluginPtr());

    if ( !share )
    {
        DEBUG_MSG("Subscriber does not implement proper interface!" << subscriber->getMetaData().value("name").toString());
        return;
    }

    shareSubscriptions.insert(publisher->getPluginPtr(),share);
    DEBUG_MSG("Subscription was successfull" << pluginName)
}

void Core::addPlugin(const QString &name, Interfaces::Plugin *plugin, QJsonObject metaData)
{
   auto it = plugins.find(name);

   if ( it != plugins.end() )
   {
       Exception::fail( ExceptionCodes::CannotAddPluginError, {name, "Already exists" });
   }

   DispatcherSPtr dispatcherSPtr = createDispatcher(plugin,metaData);
   initializeDispatcher(dispatcherSPtr);
   plugins.insert(name,dispatcherSPtr);
   DEBUG_MSG("Plugin added:" << name);
}


void Core::initPlugins()
{
    auto it = plugins.begin();
    for ( auto it = plugins.begin(); it != plugins.end();)
    {
        Interfaces::Plugin *bootprints_plugin = it.value()->getPluginPtr();
        if (bootprints_plugin)
        {
            DEBUG_MSG("Initialize plugin:" << it.key())
            try
            {
                bootprints_plugin->init(it.value().data());
                ++it;
            }catch(exception)
            {
                DEBUG_MSG("Exception happend in plugin "  )
                ++it;
                plugins.remove(it.key());
            }
        }
    }
}

QStringList Core::addPlugins(const QDir &pluginsDir)
{
    QStringList lsProblems;

#ifdef __linux__
    const QStringList nameFilters = {"*.so"};
#elif defined(_WIN32)
    const QStringList nameFilters = {"*.dll"};
#else
#warning "Could not get OS type!"
    const QStringList nameFilters = {"*.so"};
#endif

    for (const QString &fileName : pluginsDir.entryList( nameFilters, QDir::Files) )
    {
        DEBUG_MSG("Try to load plugin:"<< fileName)
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        const auto metadata = pluginLoader.metaData().value("MetaData").toObject();
        if ( !metadata.contains("name") ){
            Exception e = Exception(
                ExceptionCodes::CannotAddPluginError,
                {fileName,"No name property was given in internal JSON data."}
            );
            DEBUG_MSG(e.toString())
            lsProblems.append(e.toString());
            continue;
        }
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
          Interfaces::Plugin *bootprints_plugin = qobject_cast<Interfaces::Plugin *>(plugin);
          if (bootprints_plugin )
          {
             QString pluginName = metadata.value("name").toString();
             try{
                addPlugin(pluginName,bootprints_plugin,metadata);
             }catch(Exception e)
             {
                 DEBUG_MSG(e.toString())
                 lsProblems.append(e.toString());
             }
             continue;
          } else
          {
              Exception e = Exception(
                  ExceptionCodes::CannotAddPluginError,
                  {fileName,"Casting to internal interface(Plugin) failed."}
              );
              DEBUG_MSG(e.toString())
              lsProblems.append(e.toString());
          }
        } else{
        Exception e = Exception(
            ExceptionCodes::CannotAddPluginError,
            {fileName,"Could not instantiate plugin. Error string:" + pluginLoader.errorString()}
        );
        DEBUG_MSG(e.toString())
        lsProblems.append(e.toString());
        }
    }

    return lsProblems;
}

