#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00[0x90];
    NNSSndArcFat *fat;
} SndArcHandle;

extern SndArcHandle *data_0205e2e4;

void *NNS_SndArcGetFileAddress_0201ee28(u32 fileId)
{
    SndArcHandle *arc = data_0205e2e4;

    if (fileId >= arc->fat->count) return NULL;
    return arc->fat->files[fileId].mem;
}
