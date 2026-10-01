#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x26];
    s8 layoutOffset;
} SceneContext;

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

typedef struct {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0060;
extern void func_ov001_0207d120(s32 value);
extern void func_ov001_0207d210(s32 value);
extern void ApplyVerticalLayoutOffset_0207d5f4(BOOL raised);
extern void func_ov001_0207d384(s32 value);
extern s32 func_ov001_02063a6c(void);
extern void func_ov021_020af57c(s32 value, s32 flag);
extern void func_ov001_0207ef40(s32 value);
extern void ResumeTaskAndClearFlags_02066780(void);
extern void func_ov001_0206c2f8(s32 value);
extern void func_ov001_02087628(int enable);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_0206e444(s32 value);
extern void UpdateEventObjects_0206daf8(void);
extern void func_ov001_0208804c(void);
extern int CacheSeqArcStatus_0204e00c(int index);

s32 ResumeSceneAndAdvance_020baa08(void) {
    SceneState *scene = data_ov032_020c0060.scene;
    func_ov001_0207d120(1);
    func_ov001_0207d120(0x41);
    func_ov001_0207d210(1);
    ApplyVerticalLayoutOffset_0207d5f4(data_ov032_020c0060.context->layoutOffset >= 0);
    func_ov001_0207d384(1);
    func_ov021_020af57c(func_ov001_02063a6c(), 0);
    func_ov001_0207ef40(0);
    ResumeTaskAndClearFlags_02066780();
    func_ov001_0206c2f8(0);
    func_ov001_02087628(0);
    if (!func_ov001_020645c8(0x3309) && scene->mode != 3) {
        func_ov001_0206e444(0);
    }
    data_ov032_020c0060.scene->flags |= 0xc;
    if (scene->mode < 0 || scene->mode == 3) {
        scene->flags &= 0xffdf;
    }
    if (!func_ov001_020645c8(0x360c)) {
        UpdateEventObjects_0206daf8();
        func_ov001_0208804c();
    }
    CacheSeqArcStatus_0204e00c(2);
    data_ov032_020c0060.scene->flags |= 0x8000;
    return 6;
}
