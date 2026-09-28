#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;

void SetCachedSoundParams_0204dcec(u32 param1, u32 param2, u16 param3)
{
    *(u32 *)(g_soundWork_0206084c + 0xb4720) = param1;
    *(u32 *)(g_soundWork_0206084c + 0xb4724) = param2;
    *(u16 *)(g_soundWork_0206084c + 0xb4728) = param3;
}
