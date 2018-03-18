
#include "core.h"

#include <QPluginLoader>



BootPrints::Core::Core()
{

}

void BootPrints::Core::addPlugin(const QString &name, BootPrints::Interfaces::BasePlugin *plugin)
{
   auto it = plugins.find(name);

   if ( it != plugins.end() )
   {
       BootPrints::Exception::fail( BootPrints::ExceptionCodes::CannotAddPluginError, {name, "Already exists" });
       return;
   }
   plugins.insert(name,plugin);
   DEBUG_MSG("Plugin added:" << name);
}

void BootPrints::Core::initPlugins()
{
    DEBUG_MSG("Nr of plugins to be initialized:" << plugins.size())
    for ( PluginHashMap::const_iterator it = plugins.begin(); it != plugins.end();++it)
    {
        DEBUG_MSG("Initialize plugin:" << it.key())
        BootPrints::Interfaces::BasePlugin *bp = *it;
        BootPrints::Interfaces::Plugin *bootprints_plugin = dynamic_cast<BootPrints::Interfaces::Plugin*>(bp);
        if (bootprints_plugin)
        {
            //TODO for now pass everything
            bootprints_plugin->init(plugins);
        }

    }
}

QStringList BootPrints::Core::addPlugins(const QDir &pluginsDir)
{
    QStringList lsProblems;

    const QStringList nameFilters = {"*.so"};

    for (const QString &fileName : pluginsDir.entryList( nameFilters, QDir::Files) )
    {
        DEBUG_MSG("Try to load plugin:"<< fileName)
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        const auto metadata = pluginLoader.metaData().value("MetaData").toObject();
        if ( !metadata.contains("name") ){
            BootPrints::Exception e = BootPrints::Exception(
                BootPrints::ExceptionCodes::CannotAddPluginError,
                {fileName,"No name property was given in internal JSON data."}
            );
            DEBUG_MSG(e.toString())
            lsProblems.append(e.toString());
            continue;
        }
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
          BootPrints::Interfaces::Plugin *bootprints_plugin = qobject_cast<BootPrints::Interfaces::Plugin *>(plugin);
          if (bootprints_plugin )
          {
             QString pluginName = metadata.value("name").toString();
             try{
                addPlugin(pluginName,bootprints_plugin);
             }catch(BootPrints::Exception e)
             {
                 DEBUG_MSG(e.toString())
                 lsProblems.append(e.toString());
             }
             continue;
          } else
          {
              BootPrints::Exception e = BootPrints::Exception(
                  BootPrints::ExceptionCodes::CannotAddPluginError,
                  {fileName,"Casting to internal interface(Plugin) failed."}
              );
              DEBUG_MSG(e.toString())
              lsProblems.append(e.toString());
          }
        } else{
        BootPrints::Exception e = BootPrints::Exception(
            BootPrints::ExceptionCodes::CannotAddPluginError,
            {fileName,"Casting to internal interface(QObject) failed."}
        );
        DEBUG_MSG(e.toString())
        lsProblems.append(e.toString());
        }
    }

    return lsProblems;
}
