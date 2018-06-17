#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QJsonObject>

#include <internal.h>
#include <plugin.h>

class Dispatcher : public QObject, public BootPrints::Interfaces::Internal
{
    Q_OBJECT
    BootPrints::Interfaces::Plugin*       plugin;
    const QJsonObject                     metaData;

public:

    Dispatcher(BootPrints::Interfaces::Plugin *plugin, const QJsonObject &metaData, QObject *parent = 0);

    BootPrints::Interfaces::Plugin *getPluginPtr() const
    {
        return plugin;
    }
    const QJsonObject & getMetaData() const
    {
        return metaData;
    }
    void addShare(const QUrl &url);
    void subscribeToShareProvider(const QString &pluginName);
    void unSubscribeFromShareProvider( const QString &pluginName);

signals:
    void newShare(const QUrl &url);
    void newSubscriptionForShare(const QString &pluginName);
    void unSubscribeShare(const QString &pluginName);
};

using DispatcherSPtr = QSharedPointer<Dispatcher>;

#endif // DISPATCHER_H
