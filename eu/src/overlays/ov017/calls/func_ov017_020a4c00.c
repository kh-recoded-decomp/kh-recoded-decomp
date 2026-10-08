#include "nitro/types.h"

extern BOOL IsState2(void *node);
extern void ResetFieldObjectToIdle(void *node);
extern void SetFieldObjectFlag5(void *node, BOOL flag);
extern void SetFieldObjectPosition_020a40fc(void *node, void *data);
extern void RefreshListHeadAndDispatch(void *node);
extern BOOL FindBusyKind4Object(void *record);
extern BOOL func_ov042_020bd7ac();

BOOL func_ov017_020a4c00(void *context, u32 unused, void *record, void *node)
{
    BOOL result;

    result = IsState2(node);
    if ((result != 0) && (result = FindBusyKind4Object(record), result == 0)) {
        ResetFieldObjectToIdle(node);
        SetFieldObjectFlag5(node, 1);
        SetFieldObjectPosition_020a40fc(node, (u8 *)context + 8);
        RefreshListHeadAndDispatch(node);
    }
    if (func_ov042_020bd7ac() == 0) {
        SetFieldObjectFlag5(node, 0);
        return 1;
    }
    return 0;
}
