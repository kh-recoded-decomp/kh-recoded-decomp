#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

BOOL NNSi_SndFaderIsFinished_02021948 (const NNSSndFader * fader)
{

    return fader->counter >= fader->frame ? TRUE : FALSE;
}
