#ifndef INTERNAL_H
#define INTERNAL_H

class MediaItem;

namespace BootPrints::Interfaces
{
    struct Internal
    {
         virtual void addNewMediaItem( MediaItem mi ) = 0;
    };
}

#include <memory>

typedef std::shared_ptr<BootPrints::Interfaces::Internal> CorePtr;

#endif // INTERNAL_H
