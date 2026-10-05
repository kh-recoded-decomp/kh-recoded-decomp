#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitSelectMenu_020bf700(void);
extern void PXI_Init_020bf99c(void);
extern void ResetMenuCursorWithSound_020bfc28(void);
extern void SelectPrevOption_020bfb88(void);
extern void TeardownSceneResources_020bf9a4(void);
extern void func_ov084_020bfbc4(void);
extern void func_ov084_020bfc08(void);

void *data_ov084_020bfc80[17] = {
    (void *)InitSelectMenu_020bf700,
    (void *)TeardownSceneResources_020bf9a4,
    (void *)PXI_Init_020bf99c,
    (void *)0x00000001,
    (void *)0x000001D4,
    (void *)SelectPrevOption_020bfb88,
    (void *)func_ov084_020bfbc4,
    NULL,
    NULL,
    (void *)func_ov084_020bfc08,
    (void *)ResetMenuCursorWithSound_020bfc28,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)ResetMenuCursorWithSound_020bfc28,
};
