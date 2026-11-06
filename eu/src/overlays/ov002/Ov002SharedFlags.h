#ifndef KH_RECODED_OV002_SHARED_FLAGS_H
#define KH_RECODED_OV002_SHARED_FLAGS_H

#include "nitro/types.h"

extern u32 gOv002ScreenFadeCompleteStorage[];
#define gScreenFadeComplete (*(u8 *)gOv002ScreenFadeCompleteStorage)

extern u32 gMenuContextCommandFlagStorage[];
#define gContextCommandFlag (*(u8 *)gMenuContextCommandFlagStorage)

#endif
