#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct {
    u32 loAddr;
    u32 hiAddr;
} PlttVramState;

typedef struct {
    u8 pad_00[0x92c];
    NNSGfdFrmTexVramState texStates[16];
    PlttVramState plttStates[16];
    u8 vramStateDepth;
} ActorRegistry;

extern void NNS_GfdGetFrmTexVramState_02013b0c(NNSGfdFrmTexVramState *state);
extern void NNS_GfdGetFrmPlttVramState_02013d3c(PlttVramState *state);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern ActorRegistry *g_actorRegistry_0206083c;

u8 PushVramState_020365a4(void)
{
    ActorRegistry *registry = g_actorRegistry_0206083c;

    if (registry->vramStateDepth < 16) {
        NNS_GfdGetFrmTexVramState_02013b0c(&registry->texStates[registry->vramStateDepth]);
        NNS_GfdGetFrmPlttVramState_02013d3c(&registry->plttStates[registry->vramStateDepth]);
        registry->vramStateDepth++;
    } else {
        RunResetCallbackAndIdle_02004cf0();
    }
    return registry->vramStateDepth;
}
