#include "nitro/types.h"

extern void func_ov002_02065c4c(void);
extern void func_ov002_02065c50(void);

const u32 gOv002MenuMainObjConfig[6] = {
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00000014, 0x00000000,
};

void *const gOv002MenuSubBgConfig[5] = {
    (void *)0x00000013,
    (void *)0x00000002,
    (void *)0x00000013,
    (void *)func_ov002_02065c4c,
    (void *)func_ov002_02065c50,
};
