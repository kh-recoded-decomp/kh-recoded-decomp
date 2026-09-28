#include "nitro/types.h"

typedef struct {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct {
    void *prevObject;
    void *nextObject;
    u32 param[10];
} StrmCommand;

typedef struct {
    void *queueHead;
    void *queueTail;
    void *owner;
    u32 tagAndCount;
} SyncObject;

typedef struct {
    u8 pad_00[0x118];
    u32 flags;
    u8 pad_11c[0x128 - 0x11c];
    int allocChannelCount;
    u8 numChannels;
    u8 pad_12d[0x134 - 0x12d];
    void *buffer;
    u32 bufSize;
    u8 pad_13c[0x150 - 0x13c];
    int playerNo;
    u8 pad_154[0x17c - 0x154];
} NNSSndStrmPlayer;

extern int data_0205e324;
extern NNSFndList data_0205e330;
extern StrmCommand data_0205e354[8];
extern SyncObject data_0205e33c;
extern u8 data_0205e4e0[0x200];
extern NNSSndStrmPlayer data_0205e6e0[4];
extern u8 data_0205ecd0[0x18c];

extern u32 func_0201288c(u32 list, u32 offset);
extern void AppendIntrusiveListObject_020128d0(void *list, void *obj);
extern void InitSyncObject_02003134(SyncObject *obj);
extern void func_0200b394(void *file);
extern void InitStrm_0201df60(void *stream);
extern BOOL ConfigureArchiveStreamPlayers_02020178(u32 heap);
extern void func_0202096c(void *thread, u32 threadPrio);

#pragma opt_rotateloops off
#pragma opt_strength_reduction off
void NNS_SndArcStrmInit_02020074(u32 threadPrio, u32 heap)
{
    int i;
    int playerNo;
    NNSSndStrmPlayer *player;

    if (data_0205e324 != 0) {
        ConfigureArchiveStreamPlayers_02020178(heap);
        return;
    }
    data_0205e324 = 1;

    func_0201288c((u32)&data_0205e330, 0);
    for (i = 0; i < 8; i++) {
        AppendIntrusiveListObject_020128d0(&data_0205e330, &data_0205e354[i]);
    }
    InitSyncObject_02003134(&data_0205e33c);

    *(u8 **)((u8 *)&data_0205e324 + 8) = data_0205e4e0;

    for (playerNo = 0; playerNo < 4; playerNo++) {
        player = &data_0205e6e0[playerNo];

        player->flags &= ~1;
        func_0200b394((u8 *)player + 0x64);
        InitStrm_0201df60(player);
        player->playerNo = playerNo;
        player->numChannels = 0;
        player->buffer = NULL;
        player->bufSize = 0;
        player->allocChannelCount = 0;
    }

    ConfigureArchiveStreamPlayers_02020178(heap);
    func_0202096c(data_0205ecd0, threadPrio);
}
#pragma opt_strength_reduction reset
#pragma opt_rotateloops reset
