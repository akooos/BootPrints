#ifndef INTERNAL_H
#define INTERNAL_H

class QUrl;
class QStringList;

namespace BootPrints::Interfaces
{
    class Plugin;
    struct Internal
    {
       virtual void addShare(  const QUrl &url ) = 0;
       virtual void subscribeToShareProvider(const QString &pluginName ) = 0;
       virtual void unSubscribeFromShareProvider(const QString &pluginName ) = 0;
    };
}



#endif // INTERNAL_H
