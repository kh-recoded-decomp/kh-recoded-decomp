#include "nitro/types.h"

typedef struct TargetInfo {
    u8 pad_00[0x6c];
    s32 type;
} TargetInfo;

typedef struct CameraTarget {
    TargetInfo *info;
    s32 kind;
} CameraTarget;

extern BOOL Camera_CanTrackTarget_020c1ba8(CameraTarget *target, void *work, void *query, void *context);

BOOL CameraTarget_IsTrackable_020c6dec(CameraTarget *target, void *work, void *query, void *context)
{
    if (target->kind == 4 && target->info->type == 0x23) {
        return FALSE;
    }
    if (!Camera_CanTrackTarget_020c1ba8(target, work, query, context)) {
        return FALSE;
    }
    return TRUE;
}


