#include "nitro/types.h"

extern u8 data_ov015_0207a1fc[];
extern u8 data_ov015_0207a208[];
extern u8 data_ov015_0207a22c[];
extern u8 data_ov015_0207a240[];
extern u8 data_ov015_0207a258[];
extern u8 data_ov015_0207a274[];
extern u8 data_ov015_0207a294[];
extern u8 data_ov015_0207e8d8[];
extern u8 data_ov015_0207e900[];
extern u8 data_ov015_0207e928[];

void (*data_ov015_0207e884[10])(void) = {
    NULL,
    NULL,
    NULL,
    (void (*)(void))data_ov015_0207a1fc,
    (void (*)(void))data_ov015_0207a208,
    (void (*)(void))data_ov015_0207a22c,
    (void (*)(void))data_ov015_0207a240,
    (void (*)(void))data_ov015_0207a258,
    (void (*)(void))data_ov015_0207a274,
    (void (*)(void))data_ov015_0207a294,
};

void (*data_ov015_0207e868[7])(void) = {
    NULL,
    (void (*)(void))data_ov015_0207e928,
    (void (*)(void))data_ov015_0207e928,
    (void (*)(void))data_ov015_0207e928,
    (void (*)(void))data_ov015_0207e928,
    (void (*)(void))data_ov015_0207e900,
    (void (*)(void))data_ov015_0207e8d8,
};
