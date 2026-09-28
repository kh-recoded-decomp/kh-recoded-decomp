#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00[0x90];
    NNSSndArcFat *fat;
} SndArcHandle;

extern SndArcHandle *data_0205e2e4;

u32 NNS_SndArcGetFileSize_0201ed14(u32 fileId)
{
    SndArcHandle *arc = data_0205e2e4;

    if (fileId >= arc->fat->count) return 0;
    return arc->fat->files[fileId].size;
}
