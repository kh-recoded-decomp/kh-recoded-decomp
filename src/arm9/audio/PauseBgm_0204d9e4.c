#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00000[0xb44d8];
    NNSSndHandle bgmHandle;
    u8 pad_b44dc[0xb472a - 0xb44dc];
    s16 currentBgmId;
} SoundWork;

extern SoundWork *g_soundWork_0206084c;
extern void NNS_SndPlayerPause_0201d5e0(NNSSndHandle *handle, BOOL flag);

void PauseBgm_0204d9e4(BOOL pause)
{
    SoundWork *work = g_soundWork_0206084c;

    if (work->currentBgmId < 0) {
        return;
    }
    NNS_SndPlayerPause_0201d5e0(&work->bgmHandle, pause);
}
