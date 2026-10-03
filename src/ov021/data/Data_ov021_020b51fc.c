#include "nitro/types.h"

extern u8 data_ov021_020b5208[];
extern u8 data_ov021_020b5218[];
extern u8 data_ov021_020b5228[];

void (*data_ov021_020b51fc[3])(void) = {
    (void (*)(void))data_ov021_020b5218,
    (void (*)(void))data_ov021_020b5208,
    (void (*)(void))data_ov021_020b5228,
};
