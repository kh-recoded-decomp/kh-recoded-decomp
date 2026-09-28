#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;

int GetCachedSoundParam_0204d720(void)
{
    return (int)*(s16 *)(g_soundWork_0206084c + 0xb472a);
}
