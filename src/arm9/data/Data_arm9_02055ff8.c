#include "nitro/types.h"

extern u8 data_02055fdc[];
extern u8 data_02055fe0[];
extern u8 data_02055fe4[];
extern u8 data_02055fe8[];
extern u8 data_02055fec[];
extern u8 data_02055ff0[];
extern u8 data_02055ff4[];

void (*data_02055ff8[7])(void) = {
    (void (*)(void))data_02055ff4,
    (void (*)(void))data_02055fe0,
    (void (*)(void))data_02055fec,
    (void (*)(void))data_02055fe8,
    (void (*)(void))data_02055fe4,
    (void (*)(void))data_02055ff0,
    (void (*)(void))data_02055fdc,
};
