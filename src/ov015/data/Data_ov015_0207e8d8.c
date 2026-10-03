#include "nitro/types.h"

extern u8 data_ov015_0207a7b8[];
extern u8 data_ov015_0207aa10[];
extern u8 data_ov015_0207b5c8[];
extern u8 data_ov015_0207bf28[];
extern u8 data_ov015_0207c180[];
extern u8 data_ov015_0207c3d8[];
extern u8 data_ov015_0207cd38[];
extern u8 data_ov015_0207d1e8[];
extern u8 data_ov015_0207d8f0[];

void (*data_ov015_0207e8d8[10])(void) = {
    (void (*)(void))data_ov015_0207cd38,
    (void (*)(void))data_ov015_0207d8f0,
    (void (*)(void))data_ov015_0207d1e8,
    (void (*)(void))data_ov015_0207a7b8,
    (void (*)(void))data_ov015_0207c3d8,
    (void (*)(void))data_ov015_0207bf28,
    (void (*)(void))data_ov015_0207b5c8,
    (void (*)(void))data_ov015_0207aa10,
    (void (*)(void))data_ov015_0207c180,
    NULL,
};
