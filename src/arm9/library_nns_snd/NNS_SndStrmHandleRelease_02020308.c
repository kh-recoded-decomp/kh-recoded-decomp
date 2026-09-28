#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x154];
    void *handle;
} NNSSndStrmPlayer;

typedef struct {
    NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

void NNS_SndStrmHandleRelease_02020308(NNSSndStrmHandle *handle)
{
    if (handle->player != NULL) {
        handle->player->handle = NULL;
        handle->player = NULL;
    }
}
