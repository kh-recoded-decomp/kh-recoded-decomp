#include "nitro/types.h"

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    u16 flags;
    s8 mode;
} SceneState;

extern SceneState *data_ov028_020bb3a0;

extern s8 func_ov001_02068084(void);
extern void LoadContextResourceGroups(int sound);
extern BOOL IsSessionFlagSet(u32 flag);
extern void SetupSlotPanelMode(int mode, int enable);
extern int func_ov001_02063a6c(void);
extern void ForwardSubModePairB(int value, int arg);
extern void SetOverlayLayerVisible(int visible);
extern void ResumeTaskAndClearFlags(void);
extern void SetMenuHighlight(int highlight);
extern void func_ov001_02087650(int value);
extern void SetFieldEntriesPaused(int paused);
extern void func_ov001_02063ff4(void);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern void CacheSeqArcStatus(int index);

int ResumeFieldFromMenu(void) {
    SceneState *scene = data_ov028_020bb3a0;

    switch (func_ov001_02068084()) {
    case 2:
        LoadContextResourceGroups(9);
        if (IsSessionFlagSet(0x3716)) {
            SetupSlotPanelMode(0, 1);
        }
        break;
    case 6:
        LoadContextResourceGroups(0x23);
        if (IsSessionFlagSet(0x3714)) {
            SetupSlotPanelMode(1, 1);
        }
        break;
    default:
        LoadContextResourceGroups(1);
        break;
    }
    ForwardSubModePairB(func_ov001_02063a6c(), 0);
    SetOverlayLayerVisible(0);
    ResumeTaskAndClearFlags();
    SetMenuHighlight(0);
    func_ov001_02087650(0);
    if (!IsSessionFlagSet(0x3309) && scene->mode != 3) {
        SetFieldEntriesPaused(0);
    }
    data_ov028_020bb3a0->flags |= 0xc;
    if (scene->mode < 0 || scene->mode == 3) {
        scene->flags &= ~0x20;
    }
    func_ov001_02063ff4();
    if (!IsSessionFlagSet(0x360c)) {
        UpdateEventObjects();
        ForwardToActiveService_02088074();
    }
    CacheSeqArcStatus(2);
    data_ov028_020bb3a0->flags |= 0x8000;
    return 6;
}
