#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

inline BOOL NNS_SndHandleIsValid (const struct NNSSndHandle * handle)
{
    return handle->player != NULL ;
}

void NNS_SndPlayerSetInitialVolume_0201d72c (NNSSndHandle * handle, int volume)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->initVolume = (u8)volume;
}
