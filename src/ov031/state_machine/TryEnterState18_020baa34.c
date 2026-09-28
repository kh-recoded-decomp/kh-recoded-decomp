#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void StoreToGlobalPtr4Field28_0202a778(u32 a);
extern void func_02036434(void);
extern void func_020365f0(void);
extern void ReleaseSeqArcHeapLevel_0204e040(u32 index);
extern void func_ov001_02063524(u32 index, u32 a, u32 b);
extern void func_ov001_020667b4(void);
extern void func_ov001_020676c4(void);
extern void func_ov001_020685d4(void);
extern void func_ov001_0206db5c(u32 index);
extern u32 func_ov001_0206dc38(void);
extern u32 func_ov001_0206dc4c(u32 index);
extern u32 func_ov001_0206dc80(u32 index);
extern void func_ov001_0206de40(u32 index);
extern u32 func_ov001_0207b36c(void);
extern void func_ov001_0207d658(void);
extern void func_ov001_0207ef40(u32 a);
extern void func_ov001_0207ef78(void);
extern void func_ov001_020828ac(void);
extern void func_ov059_020cbdd0(void);

u32 TryEnterState18_020baa34(void)
{
    int result;
    u32 a;
    u32 b;
    int index;

    if ((g_activeState_020bc800->flags & 0x10) == 0) {
        result = func_ov001_0207b36c();
        if (result == 0) {
            return 0xffffffff;
        }
    }
    func_ov001_020667b4();
    func_ov001_020828ac();
    index = 0;
    result = func_ov001_0206dc38();
    if (0 < result) {
        do {
            func_ov001_0206db5c(index);
            func_ov059_020cbdd0();
            func_ov001_0206de40(index);
            a = func_ov001_0206dc4c(index);
            b = func_ov001_0206dc80(index);
            func_ov001_02063524(index, a, b);
            index = index + 1;
            result = func_ov001_0206dc38();
        } while (index < result);
    }
    func_ov001_020685d4();
    func_ov001_020676c4();
    func_ov001_0207ef40(1);
    func_ov001_0207ef78();
    g_activeState_020bc800->flags = g_activeState_020bc800->flags & 0xfff3;
    func_ov001_0207d658();
    func_020365f0();
    func_02036434();
    ReleaseSeqArcHeapLevel_0204e040(1);
    StoreToGlobalPtr4Field28_0202a778(1);
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
    return 0x12;
}
