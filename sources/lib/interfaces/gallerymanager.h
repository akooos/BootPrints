#ifndef GALLERYMANAGER_H
#define GALLERYMANAGER_H

#include "plugin.h"

namespace BootPrints::Interfaces
{
   struct GalleryManager : Plugin
   {
       virtual void read(unsigned int offset, unsigned int limit) = 0;
   };
}

#define GalleryManager_iid "org.Akooos.BootPrints.GalleryManager"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::GalleryManager, GalleryManager_iid)

#endif // GALLERYMANAGER_H
