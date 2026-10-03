#include "nitro/types.h"

extern u8 data_ov097_020c1dd8[];
extern u8 data_ov097_020c1dec[];
extern u8 data_ov097_020c1e04[];

void (*data_ov097_020c1dc0[3])(void) = {
    (void (*)(void))data_ov097_020c1dd8,
    (void (*)(void))data_ov097_020c1dec,
    (void (*)(void))data_ov097_020c1e04,
};
