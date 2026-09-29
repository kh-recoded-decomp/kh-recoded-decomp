#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct {
    u32 loAddr;
    u32 hiAddr;
} PlttVramState;

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a;
    u8 vramDepth;
} ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[0x200];
    u8 pad_820[0x10c];
    NNSGfdFrmTexVramState texStates[16];
    PlttVramState plttStates[16];
    u8 vramStateDepth;
} ActorRegistry;

extern void NNS_GfdSetFrmTexVramState_02013b50(const NNSGfdFrmTexVramState *state);
extern void NNS_GfdSetFrmPlttVramState_02013d58(const PlttVramState *state);
extern void Obj_ConditionalShutdown_020368c8(ActorSlot *slot, u16 index);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern ActorRegistry *g_actorRegistry_0206083c;

void PopVramState_020365f0(void)
{
    ActorRegistry *registry = g_actorRegistry_0206083c;
    int i;

    if (registry->vramStateDepth == 0) {
        RunResetCallbackAndIdle_02004cf0();
    }
    for (i = 0; i < 0x200; i++) {
        ActorSlot *slot = registry->slots[i];
        if (slot != NULL && slot->vramDepth >= registry->vramStateDepth && (slot->flags & 0x800) == 0) {
            Obj_ConditionalShutdown_020368c8(slot, i);
        }
    }
    registry->vramStateDepth--;
    NNS_GfdSetFrmTexVramState_02013b50(&registry->texStates[registry->vramStateDepth]);
    NNS_GfdSetFrmPlttVramState_02013d58(&registry->plttStates[registry->vramStateDepth]);
}
