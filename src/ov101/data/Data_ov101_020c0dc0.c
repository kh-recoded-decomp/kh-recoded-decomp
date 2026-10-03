#include "nitro/types.h"

extern u8 data_ov101_020c0de0[];
extern u8 data_ov101_020c0df0[];
extern u8 data_ov101_020c0e00[];
extern u8 data_ov101_020c0e18[];
extern u8 data_ov101_020c0e34[];
extern u8 data_ov101_020c0e54[];
extern u8 data_ov101_020c0e74[];

void (*data_ov101_020c0dcc[5])(void) = {
    (void (*)(void))data_ov101_020c0e00,
    (void (*)(void))data_ov101_020c0e18,
    (void (*)(void))data_ov101_020c0e34,
    (void (*)(void))data_ov101_020c0df0,
    (void (*)(void))data_ov101_020c0de0,
};

void (*data_ov101_020c0dc0[3])(void) = {
    (void (*)(void))data_ov101_020c0e54,
    (void (*)(void))data_ov101_020c0e74,
    NULL,
};
