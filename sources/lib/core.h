#ifndef BOOTPRINTS_H
#define BOOTPRINTS_H

#include <QMultiHash>
#include <QDir>
#include <QVector>

#include <share.h>
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

        QMultiHash<BootPrints::Interfaces::Plugin*,BootPrints::Interfaces::Share*> shareSubscriptions;
        void addPlugin(const QString &name, BootPrints::Interfaces::Plugin *plugin, QJsonObject metaData);
     public:

        Core( QObject *parent = 0 );

        QStringList addPlugins(const QDir &pluginsDir);
        void initPlugins();
        void disposePlugins();

      protected:
        virtual DispatcherSPtr createDispatcher(Interfaces::Plugin *plugin, const QJsonObject &metaData);
        virtual void initializeDispatcher(DispatcherSPtr dispatcher);

      private slots:
        void onNewSubscribeForShare(const QString &pluginName);
        void onNewShare(const QUrl &url);
    };
}

#endif // BOOTPRINTS_H
