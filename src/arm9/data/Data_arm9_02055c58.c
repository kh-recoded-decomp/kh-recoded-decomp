#include "nitro/types.h"

extern u8 data_02055c78[];
extern u8 data_02055c90[];
extern u8 data_02055ca8[];
extern u8 data_02055cc0[];
extern u8 data_02055cd8[];
extern void func_02013774(void);

void (*data_02055c64[5])(void) = {
    (void (*)(void))data_02055cd8,
    (void (*)(void))data_02055cc0,
    (void (*)(void))data_02055c78,
    (void (*)(void))data_02055ca8,
    (void (*)(void))data_02055c90,
};

void (*data_02055c5c[2])(void) = {
    (void (*)(void))data_02055c78,
    (void (*)(void))data_02055cc0,
};

void (*data_02055c58[1])(void) = {
    func_02013774,
};
