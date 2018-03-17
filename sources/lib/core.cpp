
#include "core.h"

#include <QPluginLoader>

#include "exception.h"


using namespace BootPrints;

Core::Core()
{

}

void Core::addPlugin(const QString &name, Interfaces::BasePlugin *plugin)
{
   auto it = plugins.find(name);

   if ( it != plugins.end() )
   {
       Exceptions::CannotAddPluginExpcetion({"Already exists:" + name }).raise();
      return;
   }
   plugins.insert(name,plugin);
}

void Core::loadPlugins(const QDir &pluginsDir)
{
    for (const QString &fileName : pluginsDir.entryList(QDir::Files) )
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        if ( pluginLoader.metaData().contains("name") ){
            Exceptions::CannotAddPluginExpcetion({"No name given in internal JSON data."}).raise();
        }
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
          Plugin *bootprints_plugin = qobject_cast<Plugin *>(plugin);
          if (bootprints_plugin )
          {
             addPlugin(pluginLoader.metaData().value("name").toString(),bootprints_plugin);
             return;
          }
        }
    }
    Exceptions::UnknownErrorExpcetion().raise();
}
