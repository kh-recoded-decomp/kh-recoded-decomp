#include "nitro/types.h"

extern u8 data_ov097_020c1e20[];
extern u8 data_ov097_020c1e3c[];
extern u8 data_ov097_020c1e5c[];

void (*data_ov097_020c1dcc[3])(void) = {
    (void (*)(void))data_ov097_020c1e20,
    (void (*)(void))data_ov097_020c1e3c,
    (void (*)(void))data_ov097_020c1e5c,
};
