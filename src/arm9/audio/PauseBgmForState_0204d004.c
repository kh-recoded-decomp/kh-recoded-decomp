#include "nitro/types.h"

typedef struct NNSSndHandle NNSSndHandle;

extern u8 *data_0206084c;
extern void NNS_SndPlayerPause_0201d4d0(NNSSndHandle *handle, BOOL flag);

void PauseBgmForState_0204d004(BOOL pause)
{
    u8 *scene = data_0206084c;

    *(s16 *)(scene + 0xb472a) = -1;
    NNS_SndPlayerPause_0201d4d0((NNSSndHandle *)(scene + 0xb44d8), pause);
    *(BOOL *)(scene + 0xb4730) = pause;
    scene[0xb472e] = 4;
}
