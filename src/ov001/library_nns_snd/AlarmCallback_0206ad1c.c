#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/pxi.h"
#include "nnsys/snd.h"

extern void StrmCallback(NNSSndStrm * stream, NNSSndStrmCallbackStatus status);
extern void StrmCallback (NNSSndStrm * stream, NNSSndStrmCallbackStatus status);

void AlarmCallback_0206ad1c (void * arg)
{
    StrmCallback((NNSSndStrm *)arg, NNS_SND_STRM_CALLBACK_INTERVAL);
}
