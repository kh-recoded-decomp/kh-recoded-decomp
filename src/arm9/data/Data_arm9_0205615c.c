#include "nitro/types.h"

extern u8 data_02056148[];
extern u8 data_0205614c[];
extern u8 data_02056150[];
extern u8 data_02056154[];

void (*data_0205615c[4])(void) = {
    (void (*)(void))data_0205614c,
    (void (*)(void))data_02056150,
    (void (*)(void))data_02056148,
    (void (*)(void))data_02056154,
};
