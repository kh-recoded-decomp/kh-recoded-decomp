#ifndef KH_RECODED_OV038_SOUND_CONTEXT_H
#define KH_RECODED_OV038_SOUND_CONTEXT_H

#include "nitro/types.h"

typedef struct Ov038SoundContext {
    u8 pad_00[6];
    u16 flags;
    u8 mode;
} Ov038SoundContext;

extern Ov038SoundContext *data_ov038_020bd160;
#define gOv038SoundContext data_ov038_020bd160

#endif
