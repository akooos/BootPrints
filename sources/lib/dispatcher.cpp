#include "dispatcher.h"

Dispatcher::Dispatcher(
        BootPrints::Interfaces::Plugin *plugin,
        const QJsonObject &metaData,
        QObject *parent
)
    : QObject(parent),
      plugin(plugin),
      metaData(metaData)
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::addMediaItem(const MediaItem &mi)
{
   emit newMediaItem(mi);
}

void Dispatcher::subscribeToShareProvider(const QString &pluginName)
{
   emit newSubscriptionForShare(pluginName);
}

void Dispatcher::unSubscribeFromShareProvider(const QString &pluginName)
{
   emit unSubscribeShare(pluginName);
}
