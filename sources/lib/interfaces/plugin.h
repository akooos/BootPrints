#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>

namespace BootPrints{
    namespace Interfaces
    {
        struct Internal;
        struct Plugin
        {
           virtual void init(Internal *core) = 0;
           virtual void dispose() = 0;
           virtual ~Plugin() = default;

        };

        using PluginHashMap =  QHash<QString,Plugin*>;
    }
}
#define Plugin_iid "org.Akooos.BootPrints.Plugin"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::Plugin, Plugin_iid)

#endif // PLUGIN_H
