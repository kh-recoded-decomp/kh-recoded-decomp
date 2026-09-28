#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct PlttVramState {
    u32 loAddr;
    u32 hiAddr;
} PlttVramState;

extern NNSGfdFrmPlttVramManager data_0205a8c4;

void NNS_GfdSetFrmPlttVramState_02013d58(const PlttVramState *state)
{
    data_0205a8c4.loAddr = state->loAddr;
    data_0205a8c4.hiAddr = state->hiAddr;
}
