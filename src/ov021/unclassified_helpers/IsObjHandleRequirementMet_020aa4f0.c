#include "nitro/types.h"

typedef struct ObjHandle {
    u32 flags;
    u8 pad04[0x60];
    s32 level;
} ObjHandle;

extern int func_ov021_020aa6e4(ObjHandle *handle, int which);

BOOL IsObjHandleRequirementMet_020aa4f0(ObjHandle *handle, int which)
{
    int required;

    if (handle->flags & 8) {
        return TRUE;
    }
    required = func_ov021_020aa6e4(handle, which);
    if (handle->flags & 0x10) {
        if (handle->flags & 0x20) {
            return TRUE;
        }
    } else if (handle->level >= required) {
        return TRUE;
    }
    return FALSE;
}
