#include "nitro/types.h"

typedef struct {
    u8 mode;
    u8 pad_01[3];
    s32 timer;
} SceneControl;

typedef struct {
    u8 pad_000[0x9ac];
    u64 stateFlags;
} PlayerEntry;

extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 startIndex);
extern int IsStageEventReady_02087c78(u32 id);
extern void StageRecord_ClearStateIfMatches_02087d4c(u32 id, u32 state);
extern PlayerEntry *GetBoundedEntryField_0206db5c(int index);
extern BOOL Camera_ReturnFromPathView_020c2fac(void);

void ClearStageEventsAndPlayerFlags_020d7404(SceneControl *control)
{
    s32 record;
    int i;

    for (record = func_ov001_02087928(); record != 0; record = func_ov001_02087944(record)) {
        if (IsStageEventReady_02087c78(record)) {
            StageRecord_ClearStateIfMatches_02087d4c(record, 9);
        }
    }
    control->timer = 0;
    control->mode = 7;
    for (i = 0; i < 3; i++) {
        GetBoundedEntryField_0206db5c(i)->stateFlags &= ~0x20000000ULL;
    }
    Camera_ReturnFromPathView_020c2fac();
}
