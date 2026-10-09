#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    BOOL active;
} PageInteractionState;

extern void RuntimeState_SetCondition(int condition);

void ShutdownPageInteractionState(PageInteractionState *state)
{
    state->active = FALSE;
    RuntimeState_SetCondition(FALSE);
}
