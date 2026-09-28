#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/pxi.h"
#include "nnsys/snd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

inline BOOL NNS_SndStrmHandleIsValid (const NNSSndStrmHandle * handle)
{
    return handle->player != NULL ;
}
extern void SNDi_FreeVoiceChannel(NNSSndStrmPlayer * player, int fadeFrame);
extern void SNDi_FreeVoiceChannel (NNSSndStrmPlayer * player, int fadeFrame);

NNSSndStrmThread * sPrepareThread = 0;
BOOL data_0204ad8c = 0;
u8 * sDecodeBuffer = 0;

void NNS_SndArcStrmStop_020202e0 (NNSSndStrmHandle * handle, int fadeFrame)
{

    if (!NNS_SndStrmHandleIsValid(handle)) return;

    SNDi_FreeVoiceChannel(handle->player, fadeFrame);
}
