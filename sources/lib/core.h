#ifndef BOOTPRINTS_H
#define BOOTPRINTS_H

#include <QMultiHash>
#include <QDir>
#include <QVector>

#include <mediaitemhandler.h>
#include <mediaitem.h>

#include <internal.h>
#include "exception.h"

#include <dispatcher.h>

#include <functional>

using DispatcherCtor = std::function<DispatcherSPtr(BootPrints::Interfaces::Plugin* plugin,const QJsonObject &metaData)>;

namespace BootPrints
{
    class Core : public QObject
    {
        Q_OBJECT

        QHash<QString,DispatcherSPtr> plugins;

        QMultiHash<BootPrints::Interfaces::Plugin*,BootPrints::Interfaces::MediaItemHandler*> mediaItemHandlers;
        void addPlugin(const QString &name, BootPrints::Interfaces::Plugin *plugin, QJsonObject metaData);
     public:

        Core( QObject *parent = 0 );
        virtual ~Core();

        QStringList addPlugins(const QDir &pluginsDir);
        void initPlugins();
        void disposePlugins();

      protected:
        virtual DispatcherSPtr createDispatcher(Interfaces::Plugin *plugin, const QJsonObject &metaData);
        virtual void initializeDispatcher(DispatcherSPtr dispatcher);

      private slots:
        void onNewSubscribeForShare(const QString &pluginName);
        void onNewMediaItem(const MediaItem &mi);
    };
}

#endif // BOOTPRINTS_H
