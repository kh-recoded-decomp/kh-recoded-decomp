#include "nitro/types.h"

extern u8 data_ov013_02074b58[];
extern u8 data_ov013_02074b6c[];
extern u8 data_ov013_02074b80[];
extern u8 data_ov013_02074b94[];
extern u8 data_ov013_02074ba8[];

void (*data_ov013_02074b20[5])(void) = {
    (void (*)(void))data_ov013_02074b58,
    (void (*)(void))data_ov013_02074b80,
    (void (*)(void))data_ov013_02074b6c,
    (void (*)(void))data_ov013_02074b94,
    (void (*)(void))data_ov013_02074ba8,
};
