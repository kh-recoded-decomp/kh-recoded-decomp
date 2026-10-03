#include "nitro/types.h"

extern void *data_ov025_020b7760;
extern void func_ov027_020b9e00(void *tiles, int row);
extern void func_ov025_020b582c(void *menu);
extern int func_ov025_020b74d8(void *slots);
extern void func_ov025_020b5858(void *menu, int count);

void RefreshRemainingCount_020b58d8(void) {
    u8 *menu = data_ov025_020b7760;
    func_ov027_020b9e00(menu + 0x64c8, 0x1a);
    func_ov025_020b582c(menu);
    func_ov025_020b5858(menu, func_ov025_020b74d8(menu + 0x64f4));
}
