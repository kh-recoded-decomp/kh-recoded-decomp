#include "nitro/types.h"

extern u8 data_ov093_020c3e9c[];
extern u8 data_ov093_020c3eb4[];
extern u8 data_ov093_020c3ecc[];
extern u8 data_ov093_020c3ee8[];
extern u8 data_ov093_020c3f04[];
extern u8 data_ov093_020c3f28[];
extern u8 data_ov093_020c3f4c[];

void (*data_ov093_020c3e8c[4])(void) = {
    (void (*)(void))data_ov093_020c3ee8,
    (void (*)(void))data_ov093_020c3f04,
    (void (*)(void))data_ov093_020c3f28,
    (void (*)(void))data_ov093_020c3f4c,
};

void (*data_ov093_020c3e80[3])(void) = {
    (void (*)(void))data_ov093_020c3e9c,
    (void (*)(void))data_ov093_020c3eb4,
    (void (*)(void))data_ov093_020c3ecc,
};
