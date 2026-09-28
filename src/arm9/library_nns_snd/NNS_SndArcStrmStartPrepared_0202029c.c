#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x118];
    u32 flags;
} NNSSndStrmPlayer;

typedef struct {
    NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

inline BOOL IsStrmHandleValid(const NNSSndStrmHandle *handle)
{
    return handle->player != NULL;
}

void NNS_SndArcStrmStartPrepared_0202029c(NNSSndStrmHandle *handle)
{
    if (!IsStrmHandleValid(handle)) return;
    handle->player->flags |= 4;
}
