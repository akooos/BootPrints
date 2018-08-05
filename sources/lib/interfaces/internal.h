#ifndef INTERNAL_H
#define INTERNAL_H

class MediaItem;
class QStringList;

#include "plugin.h"

namespace BootPrints
{
  namespace Interfaces
  {
    struct Internal
    {
       virtual void addMediaItem( const MediaItem &mi ) = 0;
       virtual void subscribeToShareProvider(const QString &pluginName ) = 0;
       virtual void unSubscribeFromShareProvider(const QString &pluginName ) = 0;
       virtual ~Internal() = default;
    };
  }
}



#endif // INTERNAL_H
