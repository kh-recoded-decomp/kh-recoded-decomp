#include "nitro/types.h"

extern u8 data_ov022_020b7c10[];
extern u8 data_ov022_020b7c20[];
extern u8 data_ov022_020b7c30[];
extern u8 data_ov022_020b7c44[];
extern u8 data_ov022_020b7c58[];
extern u8 data_ov022_020b7c70[];

void (*data_ov022_020b7bf8[6])(void) = {
    (void (*)(void))data_ov022_020b7c70,
    (void (*)(void))data_ov022_020b7c10,
    (void (*)(void))data_ov022_020b7c30,
    (void (*)(void))data_ov022_020b7c58,
    (void (*)(void))data_ov022_020b7c20,
    (void (*)(void))data_ov022_020b7c44,
};
