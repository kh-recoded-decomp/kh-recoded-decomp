#include "nitro/types.h"

extern u8 data_ov038_020bbdbc[];
extern u8 data_ov038_020bbdcc[];
extern u8 data_ov038_020bbde0[];

void (*data_ov038_020bbdb0[3])(void) = {
    (void (*)(void))data_ov038_020bbdbc,
    (void (*)(void))data_ov038_020bbdcc,
    (void (*)(void))data_ov038_020bbde0,
};
