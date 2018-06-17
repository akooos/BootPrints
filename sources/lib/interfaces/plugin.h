#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>

namespace BootPrints{
    namespace Interfaces
    {
        class Internal;
        class Plugin;
        typedef QHash<QString,BootPrints::Interfaces::Plugin*> PluginHashMap;

        struct Plugin
        {
           virtual void init(BootPrints::Interfaces::Internal *core) = 0;
           virtual void dispose() = 0;

        };
    }
}
#define Plugin_iid "org.Akooos.BootPrints.Plugin"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::Plugin, Plugin_iid)

#endif // PLUGIN_H
