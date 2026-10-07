#ifndef KH_RECODED_OV002_SAVE_DATA_H
#define KH_RECODED_OV002_SAVE_DATA_H

#include "nitro/types.h"

typedef struct Ov002SaveData {
    u8 pad_0000[0xcb4];
    u8 contextConfig[0x1ab8];
    u8 packedFields[0x1c];
    u8 recordFlagBits[1];
} Ov002SaveData;

extern Ov002SaveData *data_0205fe0c;
#define gSaveData data_0205fe0c

#endif
