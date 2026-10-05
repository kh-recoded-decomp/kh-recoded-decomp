#include "nitro/types.h"

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    u16 flags;
    s8 mode;
} SceneState;

extern SceneState *data_ov028_020bb380;

extern s8 GetCtxModeByte_02068084(void);
extern void func_ov001_0207d120(int sound);
extern BOOL func_ov001_020645c8(u32 flag);
extern void SetupSlotPanelMode_020640d8(int mode, int enable);
extern int func_ov001_02063a6c(void);
extern void ForwardSubModePairB_020af57c(int value, int arg);
extern void SetOverlayLayerVisible_0207ef40(int visible);
extern void ResumeTaskAndClearFlags_02066780(void);
extern void SetMenuHighlight_0206c2f8(int highlight);
extern void func_ov001_02087628(int value);
extern void SetFieldEntriesPaused_0206e444(int paused);
extern void func_ov001_02063ff4(void);
extern void UpdateEventObjects_0206daf8(void);
extern void func_ov001_0208804c(void);
extern void CacheSeqArcStatus_0204e00c(int index);

int ResumeFieldFromMenu_020ba7dc(void) {
    SceneState *scene = data_ov028_020bb380;

    switch (GetCtxModeByte_02068084()) {
    case 2:
        func_ov001_0207d120(9);
        if (func_ov001_020645c8(0x3716)) {
            SetupSlotPanelMode_020640d8(0, 1);
        }
        break;
    case 6:
        func_ov001_0207d120(0x23);
        if (func_ov001_020645c8(0x3714)) {
            SetupSlotPanelMode_020640d8(1, 1);
        }
        break;
    default:
        func_ov001_0207d120(1);
        break;
    }
    ForwardSubModePairB_020af57c(func_ov001_02063a6c(), 0);
    SetOverlayLayerVisible_0207ef40(0);
    ResumeTaskAndClearFlags_02066780();
    SetMenuHighlight_0206c2f8(0);
    func_ov001_02087628(0);
    if (!func_ov001_020645c8(0x3309) && scene->mode != 3) {
        SetFieldEntriesPaused_0206e444(0);
    }
    data_ov028_020bb380->flags |= 0xc;
    if (scene->mode < 0 || scene->mode == 3) {
        scene->flags &= ~0x20;
    }
    func_ov001_02063ff4();
    if (!func_ov001_020645c8(0x360c)) {
        UpdateEventObjects_0206daf8();
        func_ov001_0208804c();
    }
    CacheSeqArcStatus_0204e00c(2);
    data_ov028_020bb380->flags |= 0x8000;
    return 6;
}
