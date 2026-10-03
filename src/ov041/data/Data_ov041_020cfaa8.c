#include "nitro/types.h"

extern u8 data_ov041_020cedac[];
extern u8 data_ov041_020cee78[];
extern u8 data_ov041_020cee7c[];
extern u8 data_ov041_020ceec0[];
extern u8 data_ov041_020ceec4[];
extern u8 data_ov041_020cef90[];

void (*data_ov041_020cfaa8[6])(void) = {
    (void (*)(void))data_ov041_020cedac,
    (void (*)(void))data_ov041_020cee78,
    (void (*)(void))data_ov041_020cee7c,
    (void (*)(void))data_ov041_020ceec0,
    (void (*)(void))data_ov041_020ceec4,
    (void (*)(void))data_ov041_020cef90,
};
