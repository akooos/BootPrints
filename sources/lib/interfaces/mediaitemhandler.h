#ifndef MEDIAITEMHANDLER_H
#define MEDIAITEMHANDLER_H

#include "plugin.h"

class MediaItem;

namespace BootPrints::Interfaces
{
    struct MediaItemHandler : virtual Plugin
    {
        virtual void newMediaItem (const MediaItem &mi) = 0 ;
        virtual ~MediaItemHandler() = default;
    };
}

#define MediaItemHandler_iid "org.Akooos.BootPrints.MediaItemHandler"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::MediaItemHandler, MediaItemHandler_iid)

#endif // MEDIAITEMHANDLER_H
