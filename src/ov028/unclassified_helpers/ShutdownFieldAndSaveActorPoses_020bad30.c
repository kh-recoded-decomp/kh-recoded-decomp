#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} FieldContext;

extern FieldContext *g_fieldContext_020bb380;
extern BOOL func_ov001_0207b36c(void);
extern void func_ov001_020667b4(void);
extern void func_ov001_0206c2f8(s32 enable);
extern s32 func_ov001_0206dc38(void);
extern void func_ov001_0206de40(s32 index);
extern VecFx32 *func_ov001_0206dc4c(s32 index);
extern u16 func_ov001_0206dc80(s32 index);
extern void func_ov001_02063524(s32 index, VecFx32 *position, u16 angle);
extern void func_ov001_020685d4(void);
extern void func_ov001_0207ef40(s32 value);
extern void func_ov001_0207ef78(void);
extern void func_ov001_020676c4(void);
extern void func_ov001_0207d658(void);
extern void func_ov001_02064d88(void);
extern void func_020365f0(void);
extern void func_02036434(void);
extern void ReleaseSeqArcHeapLevel_0204e040(int index);
extern void StoreToGlobalPtr4Field28_0202a778(int value);

s32 ShutdownFieldAndSaveActorPoses_020bad30(void)
{
    s32 index;
    VecFx32 *position;

    if ((g_fieldContext_020bb380->flags & 0x10) == 0 && !func_ov001_0207b36c()) {
        return -1;
    }
    func_ov001_020667b4();
    func_ov001_0206c2f8(1);
    for (index = 0; index < func_ov001_0206dc38(); index++) {
        func_ov001_0206de40(index);
        position = func_ov001_0206dc4c(index);
        func_ov001_02063524(index, position, func_ov001_0206dc80(index));
    }
    func_ov001_020685d4();
    func_ov001_0207ef40(1);
    func_ov001_0207ef78();
    func_ov001_020676c4();
    g_fieldContext_020bb380->flags &= ~0xC;
    func_ov001_0207d658();
    func_ov001_02064d88();
    func_020365f0();
    func_02036434();
    ReleaseSeqArcHeapLevel_0204e040(1);
    StoreToGlobalPtr4Field28_0202a778(1);
    g_fieldContext_020bb380->flags |= 0x8000;
    return 0x12;
}
