#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyMenuScene_020beb84(void);
extern void HandleListScrollDown(void);
extern void HandleListScrollUp(void);
extern void InitMenuScene_020beb40(void);
extern void RunSceneStateHandler(void);
extern void func_ov103_020becc4(void);
extern void func_ov103_020bed20(void);

u32 data_ov103_020c0608[60] = {
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

void *data_ov103_020c05c4[17] = {
    (void *)InitMenuScene_020beb40,
    (void *)DestroyMenuScene_020beb84,
    (void *)RunSceneStateHandler,
    (void *)0x0000000A,
    (void *)0x0000CBC4,
    (void *)HandleListScrollDown,
    (void *)HandleListScrollUp,
    NULL,
    NULL,
    (void *)func_ov103_020becc4,
    (void *)func_ov103_020bed20,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
