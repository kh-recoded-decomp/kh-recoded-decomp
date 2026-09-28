#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x120];
    s32 isSuspended;
    s32 unk_124;
    u8 pad_128[0x14];
    s32 unk_13C;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern u32 func_01ff80d4(void);
extern void *GetSceneTagTracker_020711b0(void);
extern BOOL IsFieldPanelHidden_0207187c(void);

void SetFieldMenuSuspended_02077b90(s32 suspend, s32 checkPanel)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;

    func_01ff80d4();
    GetSceneTagTracker_020711b0();
    menu->isSuspended = suspend;
    if (suspend == 0) {
        menu->unk_13C = 1;
        return;
    }
    if (checkPanel != 0 && IsFieldPanelHidden_0207187c()) {
        menu->unk_124 = 1;
    }
}
