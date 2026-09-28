#include "nitro/types.h"

extern u32 g_context_020b7520;
extern BOOL DestroyFndObjectList_020014f0(int container);
extern void func_02001474(u32 target);
extern void func_ov027_020ba294(u32 target);

void TeardownContextState_020b6730(void) {
    DestroyFndObjectList_020014f0(g_context_020b7520 + 0x6524);
    if (*(int *)(g_context_020b7520 + 0x66e0) != 0) {
        func_02001474(g_context_020b7520 + 0x650c);
        func_02001474(g_context_020b7520 + 0x6518);
    }
    func_ov027_020ba294(g_context_020b7520 + 0x6500);
}
