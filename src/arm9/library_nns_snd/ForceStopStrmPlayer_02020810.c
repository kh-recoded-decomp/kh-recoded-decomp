#include "nitro/types.h"

typedef struct StrmPlayer StrmPlayer;

struct StrmPlayer {
    u8 stream[0x118];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    u8 pad_11c[0x178 - 0x11c];
    void (*cancelStreamFunc)(StrmPlayer *player);
};

typedef struct PrepareThreadHolder {
    u32 initialized;
    u8 *prepareThread;
} PrepareThreadHolder;

extern u8 g_streamMutex_0205fd98[];
extern PrepareThreadHolder g_prepareThreadHolder_0205e324;
extern void LockSyncObjectRetry_02003158(void *mutex);
extern void ReleaseSyncObject_020031a8(void *mutex);
extern void NNS_SndStrmStop_0201e24c(StrmPlayer *stream);
extern void StopStreamPlayer_020208a8(StrmPlayer *player);

void ForceStopStrmPlayer_02020810(StrmPlayer *player)
{
    LockSyncObjectRetry_02003158(g_streamMutex_0205fd98);
    if (g_prepareThreadHolder_0205e324.prepareThread != NULL) {
        LockSyncObjectRetry_02003158(g_prepareThreadHolder_0205e324.prepareThread + 0x10c8);
    }

    if (player->playFlag) {
        NNS_SndStrmStop_0201e24c(player);
    }

    if (player->activeFlag) {
        player->cancelStreamFunc(player);
    }

    StopStreamPlayer_020208a8(player);

    ReleaseSyncObject_020031a8(g_streamMutex_0205fd98);
    if (g_prepareThreadHolder_0205e324.prepareThread != NULL) {
        ReleaseSyncObject_020031a8(g_prepareThreadHolder_0205e324.prepareThread + 0x10c8);
    }
}
