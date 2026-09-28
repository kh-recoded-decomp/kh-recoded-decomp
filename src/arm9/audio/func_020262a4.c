#include "nitro/types.h"

extern s8 data_02055e00[];
extern int GetCachedSoundParam_0204d720(void);

u32 func_020262a4(s32 soundId)
{
    s32 cachedParam = GetCachedSoundParam_0204d720();
    s32 marker = data_02055e00[0];

    return !(soundId == marker && (cachedParam == -1 || cachedParam == marker));
}
