#include "nitro/types.h"

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
} PopupStateMachine;

void SetPopupState_020c2784(PopupStateMachine *machine, s32 state)
{
    machine->state = state;
    machine->stateTimer = 0;
}
