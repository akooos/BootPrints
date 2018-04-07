#ifndef BOOTPRINTS_H
#define BOOTPRINTS_H

#include <QHash>
#include <QDir>
#include <QVector>

#include <plugin.h>
#include "exception.h"

#include <mediaitem.h>

namespace BootPrints
{
    class Core : public BootPrints::Interfaces::Internal
    {
        typedef QHash<QString,BootPrints::Interfaces::BasePlugin*> PluginHashMap;
        PluginHashMap plugins;

        QVector<BootPrints::Interfaces::Plugin*> newMediaItemSignalListeners;

      public:
        Core();
        void addPlugin(const QString &name, BootPrints::Interfaces::BasePlugin *plugin);
        QStringList addPlugins(const QDir &pluginsDir);
        void initPlugins();

        void addNewMediaItem( MediaItem mi );
    };
}

#endif // BOOTPRINTS_H
