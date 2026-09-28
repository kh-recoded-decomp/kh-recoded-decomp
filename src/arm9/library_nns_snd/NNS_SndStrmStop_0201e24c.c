#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 activeFlag : 1;
    s32 startFlag : 1;
} NNSSndStrm;

extern void ForceStopStrm_0201e304(NNSSndStrm *stream);

void NNS_SndStrmStop_0201e24c(NNSSndStrm *stream)
{
    if (!stream->activeFlag) {
        return;
    }
    ForceStopStrm_0201e304(stream);
}
