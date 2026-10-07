#include "src/overlays/ov001/FieldTaskState.h"

extern void func_ov001_020695b8(FieldTaskState *node);

FieldTaskState *ResetRangeTriggerNode(FieldTaskState *node)
{
    node->update = func_ov001_020695b8;
    node->active = FALSE;
    return node;
}
