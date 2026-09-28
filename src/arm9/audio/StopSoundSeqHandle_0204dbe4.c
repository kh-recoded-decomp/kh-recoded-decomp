#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern void NNS_SndPlayerPause_0201d4d0(void *handle, BOOL flag);
extern void func_0204ccf0(void *entry);

void StopSoundSeqHandle_0204dbe4(u32 handle)
{
    u8 *entry = g_soundWork_0206084c + 0xb4518 + (handle >> 24) * 0x20;

    if (*(u16 *)(entry + 0x14) == 0) {
        return;
    }
    if (*(u32 *)(entry + 0x18) != (handle & 0xffffff)) {
        return;
    }
    NNS_SndPlayerPause_0201d4d0(entry + 0x1c, 0);
    func_0204ccf0(entry);
}
