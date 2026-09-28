#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

inline BOOL NNS_SndHandleIsValid (const struct NNSSndHandle * handle)
{
    return handle->player != NULL ;
}

void NNS_SndHandleReleaseSeq_0201d6a4 (NNSSndHandle * handle)
{

    if (!NNS_SndHandleIsValid(handle)) return;

    handle->player->handle = NULL;
    handle->player = NULL;
}
