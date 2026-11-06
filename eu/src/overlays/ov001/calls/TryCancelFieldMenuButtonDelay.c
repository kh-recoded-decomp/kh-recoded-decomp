#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x144];
    s32 unk_144;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle gFieldCommandMenuGlobals;

extern void *GetSceneTagTracker(void);
extern BOOL InvokeFieldMinigameActiveCallback(void);
extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsLeadEntryFlag80Set(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void InvokeCallback40(void *pool, void *record);

BOOL TryCancelFieldMenuButtonDelay(void)
{
    void *pool = GetSceneTagTracker();

    if (InvokeFieldMinigameActiveCallback()) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear()) {
        return FALSE;
    }
    if (IsLeadEntryFlag80Set()) {
        return FALSE;
    }
    InvokeCallback40(pool, FindActiveRecordById(pool, 0x5d));
    InvokeCallback40(pool, FindActiveRecordById(pool, 0x5b));
    InvokeCallback40(pool, FindActiveRecordById(pool, 0x5c));
    gFieldCommandMenuGlobals.menu->unk_144 = -1;
    return TRUE;
}
