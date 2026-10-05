#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ConfigMenu_CursorDown_020c4ac8(void);
extern void ConfigMenu_CursorUp_020c4aa0(void);
extern void ConfigMenu_Init_020c4260(void);
extern void ConfigMenu_NextPage_020c4ba0(void);
extern void ConfigMenu_NextValue_020c4b24(void);
extern void ConfigMenu_PrevPage_020c4b54(void);
extern void ConfigMenu_PrevValue_020c4af4(void);
extern void ConfigMenu_Release_020c46b8(void);
extern void ConfigMenu_UpdateHelp_020c4608(void);
extern void func_ov079_020c4bec(void);

void *data_ov079_020c4c40[17] = {
    (void *)ConfigMenu_Init_020c4260,
    (void *)ConfigMenu_Release_020c46b8,
    (void *)ConfigMenu_UpdateHelp_020c4608,
    NULL,
    (void *)0x000001C0,
    (void *)ConfigMenu_CursorUp_020c4aa0,
    (void *)ConfigMenu_CursorDown_020c4ac8,
    (void *)ConfigMenu_PrevValue_020c4af4,
    (void *)ConfigMenu_NextValue_020c4b24,
    (void *)ConfigMenu_NextValue_020c4b24,
    (void *)func_ov079_020c4bec,
    NULL,
    NULL,
    (void *)ConfigMenu_PrevPage_020c4b54,
    (void *)ConfigMenu_NextPage_020c4ba0,
    NULL,
    (void *)func_ov079_020c4bec,
};
