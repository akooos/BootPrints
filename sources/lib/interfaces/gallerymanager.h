#ifndef GALLERYMANAGER_H
#define GALLERYMANAGER_H

#include "plugin.h"

namespace BootPrints
{
 namespace Interfaces
 {
   struct GalleryManager : BootPrints::Interfaces::Plugin
   {
       virtual void read(unsigned int offset, unsigned int limit) = 0;
   };
 }
}

#endif // GALLERYMANAGER_H
