#ifndef BOOTPRINTS_H
#define BOOTPRINTS_H

#include <QHash>
#include <QDir>

#include <plugin.h>

using namespace BootPrints::Interfaces;

namespace BootPrints {
    class Core
    {
        QHash<QString,BasePlugin*>  plugins;
    public:
        Core();
        void addPlugin(const QString &name, BasePlugin *plugin);
        void loadPlugins(const QDir &pluginsDir);
    };
}

#endif // BOOTPRINTS_H
