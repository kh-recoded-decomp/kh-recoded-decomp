#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CreateBoardScreen(void);
extern void DestroyBoardScreen(void);

void *data_ov024_020b74a0[5] = {
    (void *)0x000E0018,
    (void *)CreateBoardScreen,
    (void *)DestroyBoardScreen,
    (void *)0x00006700,
    NULL,
};
