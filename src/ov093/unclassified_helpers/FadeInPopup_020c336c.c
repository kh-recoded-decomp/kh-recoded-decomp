#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)((float)(n) > 0 ? 0.5f + 4096.0f * (float)(n) : 4096.0f * (float)(n) - 0.5f))

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_ov093_020c369c(StateMachine *machine, fx32 progress);
extern void StateMachine_SetState_020c3bc4(StateMachine *machine, int state);
extern void SetBgSubLayerVisible_020c3b5c(StateMachine *machine, BOOL visible);

void FadeInPopup_020c336c(StateMachine *machine)
{
    fx32 progress = FX_Div_01ff9c84(INT_TO_FX32(machine->frameCount), 0x2000);

    func_ov093_020c369c(machine, progress);
    if (progress == 0x1000) {
        StateMachine_SetState_020c3bc4(machine, 4);
    }
    SetBgSubLayerVisible_020c3b5c(machine, TRUE);
    machine->frameCount++;
}
