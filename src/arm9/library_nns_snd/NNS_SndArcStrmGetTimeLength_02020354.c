#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xcc];
    u16 sampleRate;
    u8 pad_ce[0xd4 - 0xce];
    u32 loopEnd;
} NNSSndStrmPlayer;

typedef struct {
    NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

extern int func_02023d54(u64 output_value, u32 divisor, int mode);

inline BOOL IsStrmHandleValid(const NNSSndStrmHandle *handle)
{
    return handle->player != NULL;
}

u32 NNS_SndArcStrmGetTimeLength_02020354(NNSSndStrmHandle *handle, void *unused0, void *unused1, void *unused2)
{
    if (!IsStrmHandleValid(handle)) return 0;

    return func_02023d54((u64)handle->player->loopEnd * 1000, handle->player->sampleRate, 0);
}
