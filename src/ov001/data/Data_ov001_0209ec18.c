#include "nitro/types.h"

extern u8 data_ov001_0209eb80[];
extern u8 data_ov001_0209eb8c[];
extern u8 data_ov001_0209eb98[];
extern u8 data_ov001_0209eba4[];
extern u8 data_ov001_0209ebb4[];
extern u8 data_ov001_0209ebc4[];
extern u8 data_ov001_0209ebd4[];
extern u8 data_ov001_0209ebe4[];
extern u8 data_ov001_0209ebf4[];

void (*data_ov001_0209ec18[9])(void) = {
    (void (*)(void))data_ov001_0209eb98,
    (void (*)(void))data_ov001_0209eb80,
    (void (*)(void))data_ov001_0209eb8c,
    (void (*)(void))data_ov001_0209ebd4,
    (void (*)(void))data_ov001_0209ebf4,
    (void (*)(void))data_ov001_0209eba4,
    (void (*)(void))data_ov001_0209ebb4,
    (void (*)(void))data_ov001_0209ebc4,
    (void (*)(void))data_ov001_0209ebe4,
};
