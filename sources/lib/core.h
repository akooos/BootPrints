#ifndef BOOTPRINTS_H
#define BOOTPRINTS_H

#include <QHash>
#include <QDir>

#include <plugin.h>
#include "exception.h"

namespace BootPrints {
    class Core
    {
        typedef QHash<QString,BootPrints::Interfaces::BasePlugin*> PluginHashMap;
        PluginHashMap plugins;
    public:
        Core();
        void addPlugin(const QString &name, BootPrints::Interfaces::BasePlugin *plugin);
        QStringList addPlugins(const QDir &pluginsDir);
        void initPlugins();
    };
}

#endif // BOOTPRINTS_H
