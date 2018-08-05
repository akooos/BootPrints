#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QJsonObject>
#include <mediaitem.h>
#include <internal.h>
#include <plugin.h>

class Dispatcher : public QObject, public BootPrints::Interfaces::Internal
{
    Q_OBJECT
    BootPrints::Interfaces::Plugin*       plugin;
    const QJsonObject                     metaData;

public:

    Dispatcher(BootPrints::Interfaces::Plugin *plugin, const QJsonObject &metaData, QObject *parent = nullptr);

    virtual ~Dispatcher();

    BootPrints::Interfaces::Plugin *getPluginPtr() const
    {
        return plugin;
    }
    const QJsonObject & getMetaData() const
    {
        return metaData;
    }
    void addMediaItem(const MediaItem &mi);
    void subscribeToShareProvider(const QString &pluginName);
    void unSubscribeFromShareProvider( const QString &pluginName);

signals:
    void newMediaItem(const MediaItem mi);
    void newSubscriptionForShare(const QString &pluginName);
    void unSubscribeShare(const QString &pluginName);
};

using DispatcherSPtr = QSharedPointer<Dispatcher>;

#endif // DISPATCHER_H
