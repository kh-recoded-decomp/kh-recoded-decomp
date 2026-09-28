#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x144];
    s32 unk_144;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *GetSceneTagTracker_020711b0(void);
extern BOOL func_ov001_02072040(void);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL func_ov001_0207531c(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);

BOOL func_ov001_02077c24(void)
{
    void *pool = GetSceneTagTracker_020711b0();

    if (func_ov001_02072040()) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear_0207259c()) {
        return FALSE;
    }
    if (func_ov001_0207531c()) {
        return FALSE;
    }
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0x5d));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0x5b));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0x5c));
    data_ov001_020a04b0.menu->unk_144 = -1;
    return TRUE;
}
