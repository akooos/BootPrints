#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>
#include <QHash>

namespace BootPrints::Interfaces{

    struct BasePlugin {
        virtual ~BasePlugin() = default;
    };

    struct Plugin : BasePlugin {
       virtual void init( QHash<QString,BasePlugin*> deps ) = 0;
       virtual void dispose() = 0;
    };
}
#define Plugin_iid "org.Akooos.BootPrints.Plugin"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::Plugin, Plugin_iid)

#endif // PLUGIN_H
