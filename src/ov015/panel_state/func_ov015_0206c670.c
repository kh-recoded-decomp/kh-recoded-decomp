#include "nitro/types.h"

typedef struct {
    u8 pad0_3 : 4;
    u8 flag4 : 1;
    u8 pad5_7 : 3;
} PanelFlagsE0;

extern void *data_ov015_0207e960;
extern void func_ov027_020b7dfc(void *block);
extern void func_ov027_020b8c58(void *block);

void func_ov015_0206c670(void) {
    PanelFlagsE0 *flags = (PanelFlagsE0 *)((u8 *)data_ov015_0207e960 + 0xe0);
    if (flags->flag4 == 0) {
        return;
    }
    flags->flag4 = 0;
    func_ov027_020b7dfc((u8 *)data_ov015_0207e960 + 0x5ac);
    func_ov027_020b8c58((u8 *)data_ov015_0207e960 + 0x644);
}
