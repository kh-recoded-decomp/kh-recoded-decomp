#include "src/overlays/ov001/FieldTaskState.h"

extern void EventTrigger_EvaluateBitChain(FieldTaskState *trigger);

FieldTaskState *ResetBitChainTrigger(FieldTaskState *trigger)
{
    trigger->update = EventTrigger_EvaluateBitChain;
    trigger->active = FALSE;
    return trigger;
}
