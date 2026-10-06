#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x144];
    s32 unk_144;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern void *GetSceneTagTracker(void);
extern BOOL func_ov001_02072040(void);
extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsLeadEntryFlag80Set(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);

BOOL func_ov001_02077c24(void)
{
    void *pool = GetSceneTagTracker();

    if (func_ov001_02072040()) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear()) {
        return FALSE;
    }
    if (IsLeadEntryFlag80Set()) {
        return FALSE;
    }
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 0x5d));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 0x5b));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 0x5c));
    data_ov001_020a04d0.menu->unk_144 = -1;
    return TRUE;
}
