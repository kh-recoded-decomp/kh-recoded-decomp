#include "nitro/types.h"

extern u8 data_ov059_020cfee0[];
extern u8 data_ov059_020cfee8[];
extern u8 data_ov059_020cfefc[];

void (*data_ov059_020cfef0[3])(void) = {
    (void (*)(void))data_ov059_020cfefc,
    (void (*)(void))data_ov059_020cfee0,
    (void (*)(void))data_ov059_020cfee8,
};
