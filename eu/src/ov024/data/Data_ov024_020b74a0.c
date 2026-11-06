#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CreateBoardScreen(void);
extern void DestroyBoardScreen(void);

void *gBoardScreenTaskDescriptor[5] = {
    (void *)0x000E0018,
    (void *)CreateBoardScreen,
    (void *)DestroyBoardScreen,
    (void *)0x00006700,
    NULL,
};
