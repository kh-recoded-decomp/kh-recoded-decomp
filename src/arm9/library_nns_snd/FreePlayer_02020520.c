#include "nitro/types.h"

typedef struct NNSSndStrmPlayer NNSSndStrmPlayer;

typedef struct {
    NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

struct NNSSndStrmPlayer {
    u8 pad_00[0x118];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    BOOL startFlag : 1;
    u8 pad_119[0x154 - 0x11c];
    NNSSndStrmHandle *handle;
};

void FreePlayer_02020520(NNSSndStrmPlayer *player)
{
    if (player->handle != NULL) {
        player->handle->player = NULL;
        player->handle = NULL;
    }

    player->activeFlag = FALSE;
    player->startFlag = FALSE;
    player->playFlag = FALSE;
}
