#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;

void SetStreamVolumePercent_0204e070(int percent)
{
    *(s16 *)(g_soundWork_0206084c + 0xb47d6) = (s16)((percent * 0x7f) / 100);
}
