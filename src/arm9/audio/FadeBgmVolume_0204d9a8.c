#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00000[0xb44d8];
    NNSSndHandle bgmHandle;
    u8 pad_b44dc[0xb472f - 0xb44dc];
    u8 bgmVolume;
} SoundWork;

extern SoundWork *g_soundWork_0206084c;
extern void func_0201d740(NNSSndHandle *handle, int targetVolume, int frames);

void FadeBgmVolume_0204d9a8(int targetVolume, int frames)
{
    func_0201d740(&g_soundWork_0206084c->bgmHandle, targetVolume, frames);
    g_soundWork_0206084c->bgmVolume = targetVolume;
}
