#include "nitro/types.h"

extern u8 data_ov015_0207e730[];
extern u8 data_ov015_0207e744[];
extern u8 data_ov015_0207e758[];
extern u8 data_ov015_0207e76c[];

void (*data_ov015_0207e720[4])(void) = {
    (void (*)(void))data_ov015_0207e744,
    (void (*)(void))data_ov015_0207e758,
    (void (*)(void))data_ov015_0207e730,
    (void (*)(void))data_ov015_0207e76c,
};
