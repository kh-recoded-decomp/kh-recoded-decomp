#include "nitro/types.h"

extern u32 g_context_0206c464;
extern u32 func_ov027_020b90a4(u32 panel, u32 index);
extern void func_ov027_020b96e4(u32 panel, u32 element);
extern void func_ov002_020643a0(void);
extern void func_ov002_02064f6c(u32 state);
extern void PlaySoundEffect_0204d924(u32 seqArcNo, u32 index);

void SelectMenuEntry4_02065ec4(void) {
    u32 element;

    *(u8 *)(g_context_0206c464 + 3) = 3;
    *(u8 *)(g_context_0206c464 + 1) = 6;
    element = func_ov027_020b90a4(g_context_0206c464 + 0x69e8, 4);
    func_ov027_020b96e4(g_context_0206c464 + 0x69e8, element);
    func_ov002_020643a0();
    func_ov002_02064f6c(4);
    PlaySoundEffect_0204d924(2, 1);
}
