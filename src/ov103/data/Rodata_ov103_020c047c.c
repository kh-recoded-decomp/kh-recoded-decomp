#include "nitro/types.h"

extern void PXI_Init_020c0470(void);
extern void func_ov103_020c0318(void);
extern void func_ov103_020c031c(void);
extern void func_ov103_020c03c8(void);

void (*const data_ov103_020c047c[4])(void) = {
    func_ov103_020c0318,
    func_ov103_020c031c,
    func_ov103_020c03c8,
    PXI_Init_020c0470,
};
