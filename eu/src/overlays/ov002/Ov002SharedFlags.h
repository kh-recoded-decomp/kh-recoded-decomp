#ifndef KH_RECODED_OV002_SHARED_FLAGS_H
#define KH_RECODED_OV002_SHARED_FLAGS_H

#include "nitro/types.h"

extern u32 data_ov002_0206c41c[];
#define gScreenFadeComplete (*(u8 *)data_ov002_0206c41c)

extern u32 data_ov002_0206c470[];
#define gContextCommandFlag (*(u8 *)data_ov002_0206c470)

#endif
