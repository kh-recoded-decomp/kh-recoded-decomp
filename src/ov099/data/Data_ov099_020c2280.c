#include "nitro/types.h"

extern u8 data_ov099_020c22c0[];
extern u8 data_ov099_020c22d4[];
extern u8 data_ov099_020c22ec[];
extern u8 data_ov099_020c2308[];
extern u8 data_ov099_020c2324[];

void (*data_ov099_020c2288[3])(void) = {
    (void (*)(void))data_ov099_020c22c0,
    (void (*)(void))data_ov099_020c22d4,
    (void (*)(void))data_ov099_020c22ec,
};

void (*data_ov099_020c2280[2])(void) = {
    (void (*)(void))data_ov099_020c2308,
    (void (*)(void))data_ov099_020c2324,
};
