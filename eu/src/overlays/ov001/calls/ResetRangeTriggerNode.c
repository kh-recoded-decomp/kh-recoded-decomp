#include "src/overlays/ov001/FieldTaskState.h"

extern void EvaluateManagedActorTrigger(FieldTaskState *node);

FieldTaskState *ResetRangeTriggerNode(FieldTaskState *node)
{
    node->update = EvaluateManagedActorTrigger;
    node->active = FALSE;
    return node;
}
