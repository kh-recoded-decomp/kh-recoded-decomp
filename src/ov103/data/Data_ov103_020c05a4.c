#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyMenuScene_020beb64(void);
extern void HandleListScrollDown_020bebc4(void);
extern void HandleListScrollUp_020bec34(void);
extern void InitMenuScene_020beb20(void);
extern void RunSceneStateHandler_020beb98(void);
extern void func_ov103_020beca4(void);
extern void func_ov103_020bed00(void);

u32 data_ov103_020c05e8[60] = {
    0x00000000, 0x0000000A, 0x00000028, 0x00000001,
    0x00000001, 0x00000001, 0x00000088, 0x00000022,
    0x00000000, 0x00000001, 0x00000002, 0x00000088,
    0x000000B2, 0x00000001, 0x00000001, 0x00000003,
    0x0000009E, 0x00000029, 0x00000000, 0x00000000,
    0x00000003, 0x0000009E, 0x00000039, 0x00000000,
    0x00000000, 0x00000003, 0x0000009E, 0x00000049,
    0x00000000, 0x00000000, 0x00000003, 0x0000009E,
    0x00000059, 0x00000000, 0x00000000, 0x00000003,
    0x0000009E, 0x00000069, 0x00000000, 0x00000000,
    0x00000003, 0x0000009E, 0x00000079, 0x00000000,
    0x00000000, 0x00000003, 0x0000009E, 0x00000089,
    0x00000000, 0x00000000, 0x00000003, 0x0000009E,
    0x00000099, 0x00000000, 0x00000000, 0x00000003,
    0x0000009E, 0x000000A9, 0x00000000, 0x00000000,
};

void *data_ov103_020c05a4[17] = {
    (void *)InitMenuScene_020beb20,
    (void *)DestroyMenuScene_020beb64,
    (void *)RunSceneStateHandler_020beb98,
    (void *)0x0000000A,
    (void *)0x0000CBC4,
    (void *)HandleListScrollDown_020bebc4,
    (void *)HandleListScrollUp_020bec34,
    NULL,
    NULL,
    (void *)func_ov103_020beca4,
    (void *)func_ov103_020bed00,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
