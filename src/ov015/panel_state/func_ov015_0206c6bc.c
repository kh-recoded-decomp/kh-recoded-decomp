#include "nitro/types.h"

typedef struct {
    u8 pad0_4 : 5;
    u8 flag5 : 1;
    u8 pad6_7 : 2;
} PanelFlagsE0b;

extern void *data_ov015_0207e960;
extern void func_ov027_020b7dfc(void *block);
extern void func_ov027_020b8c58(void *block);

void func_ov015_0206c6bc(void) {
    PanelFlagsE0b *flags = (PanelFlagsE0b *)((u8 *)data_ov015_0207e960 + 0xe0);
    if (flags->flag5 == 0) {
        return;
    }
    flags->flag5 = 0;
    func_ov027_020b7dfc((u8 *)data_ov015_0207e960 + 0x5f8);
    func_ov027_020b8c58((u8 *)data_ov015_0207e960 + 0x6ac0);
}
