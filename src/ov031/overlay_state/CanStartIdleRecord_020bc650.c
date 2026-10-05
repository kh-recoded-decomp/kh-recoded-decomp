#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    s32 kind;
    u8 pad_08[0x34];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    s32 nextRecordIndex;
    u8 pad_4c[0x4];
    ActiveRecord *records;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

BOOL CanStartIdleRecord_020bc650(s32 mode)
{
    BOOL result = FALSE;
    BOOL allowed = FALSE;

    if (!(g_activeState_020bc800->records[g_activeState_020bc800->recordIndex].kind == 1 || mode == 2)) {
        allowed = TRUE;
    }
    if (allowed && g_activeState_020bc800->nextRecordIndex == -1) {
        result = TRUE;
    }
    return result;
}
