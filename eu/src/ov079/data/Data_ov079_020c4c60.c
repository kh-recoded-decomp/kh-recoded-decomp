#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ConfigMenu_CursorDown(void);
extern void ConfigMenu_CursorUp(void);
extern void ConfigMenu_Init(void);
extern void ConfigMenu_NextValue(void);
extern void ConfigMenu_PrevValue(void);
extern void ConfigMenu_Release(void);
extern void ConfigMenu_UpdateHelp(void);
extern void ConfigMenu_PrevPage(void);
extern void ConfigMenu_NextPage(void);
extern void func_ov079_020c4c0c(void);

void *data_ov079_020c4c60[17] = {
    (void *)ConfigMenu_Init,
    (void *)ConfigMenu_Release,
    (void *)ConfigMenu_UpdateHelp,
    NULL,
    (void *)0x000001C0,
    (void *)ConfigMenu_CursorUp,
    (void *)ConfigMenu_CursorDown,
    (void *)ConfigMenu_PrevValue,
    (void *)ConfigMenu_NextValue,
    (void *)ConfigMenu_NextValue,
    (void *)func_ov079_020c4c0c,
    NULL,
    NULL,
    (void *)ConfigMenu_PrevPage,
    (void *)ConfigMenu_NextPage,
    NULL,
    (void *)func_ov079_020c4c0c,
};
