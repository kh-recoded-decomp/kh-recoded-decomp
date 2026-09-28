#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

void NNSi_SndPlayerPause(NNSSndSeqPlayer * seqPlayer, BOOL flag);
extern void NNSi_SndPlayerPause (NNSSndSeqPlayer * seqPlayer, BOOL flag);

void NNS_SndPlayerPause_0202a168 (NNSSndHandle * handle, BOOL flag)
{
    NNSi_SndPlayerPause(handle->player, flag);
}
