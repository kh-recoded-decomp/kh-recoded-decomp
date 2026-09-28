#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

extern NNSSndPlayer data_0205dcf8[ 32 ];

void NNS_SndPlayerSetAllocatableChannel_0201d434 (int playerNo, u32 chBitFlag)
{

    data_0205dcf8[ playerNo ].allocChBitFlag = chBitFlag;
}
