#ifndef GALLERYMANAGER_H
#define GALLERYMANAGER_H

#include "plugin.h"

namespace BootPrints
{
 namespace Interfaces
 {
   struct GalleryManager : Plugin
   {
       virtual void read(unsigned int offset, unsigned int limit) = 0;
   };
 }
}

#endif // GALLERYMANAGER_H
