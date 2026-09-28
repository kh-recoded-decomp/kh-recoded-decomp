#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

void NNSi_SndFaderUpdate_02021930 (NNSSndFader * fader)
{

    if (fader->counter < fader->frame) {
        fader->counter++;
    }
}
