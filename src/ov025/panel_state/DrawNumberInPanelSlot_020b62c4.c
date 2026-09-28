#include "nitro/types.h"

extern u32 g_uiContext_020b7760;

extern void func_02001574(void *entry, int mode);
extern int func_ov001_02073684(void);
extern int func_ov001_020711d4(void);
extern void func_0200160c(int *context, u32 x, u32 y, u32 color, u32 flags, int value,
                           u32 overrideValue, int maxWidth);
extern void func_02001520(void *entry);

void DrawNumberInPanelSlot_020b62c4(void) {
    u32 ctx = g_uiContext_020b7760;
    u32 slot = ctx + 0x6668;
    int value;
    int overrideValue;

    func_02001574((void *)slot, 0);
    value = func_ov001_02073684();
    overrideValue = func_ov001_020711d4();
    func_0200160c((int *)slot, 4, 0, 2, 0x209, value, overrideValue, 0x70);
    func_02001520((void *)slot);
}
