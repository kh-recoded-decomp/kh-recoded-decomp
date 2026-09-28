#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

extern NNSSndPlayer data_0205dcf8[ 32 ];

int NNS_SndPlayerCountPlayingSeqByPlayerNo_0201d6c0 (int playerNo)
{
    return data_0205dcf8[playerNo].playerList.numObjects;
}
