#include "nitro/types.h"

extern u32 g_context_0206c464;
extern u32 func_ov027_020b90a4(u32 target, u32 index);
extern void func_ov027_020b96e4(u32 target, u32 value);
extern void func_ov002_020643a0(void);
extern void func_ov002_02064f6c(u32 value);
extern void func_0204d924(u32 a, u32 b);

void func_ov002_02065dfc(void) {
    u32 selected;

    *(u8 *)(g_context_0206c464 + 1) = 3;
    *(u8 *)(g_context_0206c464 + 3) = 1;
    selected = func_ov027_020b90a4(g_context_0206c464 + 0x69e8, 2);
    func_ov027_020b96e4(g_context_0206c464 + 0x69e8, selected);
    func_ov002_020643a0();
    func_ov002_02064f6c(4);
    func_0204d924(2, 1);
}
