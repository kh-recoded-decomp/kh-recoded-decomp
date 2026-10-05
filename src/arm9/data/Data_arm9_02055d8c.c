#include "nitro/types.h"

#pragma explicit_zero_data on

extern u8 data_02060394[];
extern u8 data_ov000_02063870[];
extern u8 data_ov001_0209e620[];
extern u8 data_ov002_0206c2c4[];
extern u8 data_ov004_02064530[];
extern void InitSceneSystem_020254f4(void);
extern void func_0202553c(void);

void *data_02055da0[24] = {
    (void *)0xFFFFFFFF,
    NULL,
    NULL,
    (void *)data_ov000_02063870,
    (void *)0x00000001,
    (void *)data_ov001_0209e620,
    (void *)0x00000002,
    (void *)data_ov002_0206c2c4,
    (void *)0x00000004,
    (void *)data_ov004_02064530,
    (void *)0xFFFFFFFF,
    NULL,
    (void *)0xFFFFFFFF,
    NULL,
    (void *)0xFFFFFFFF,
    NULL,
    (void *)0xFFFFFFFF,
    NULL,
    (void *)0xFFFFFFFF,
    NULL,
    (void *)0xFFFFFFFF,
    NULL,
    (void *)0xFFFFFFFF,
    NULL,
};

void *data_02055d8c[5] = {
    (void *)0x00110000,
    (void *)InitSceneSystem_020254f4,
    (void *)func_0202553c,
    (void *)0x00000008,
    (void *)data_02060394,
};
