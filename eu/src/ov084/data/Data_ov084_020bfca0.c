#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ResetMenuCursorWithSound(void);
extern void SelectPrevOption(void);
extern void TeardownSceneResources(void);
extern void InitSelectMenu(void);
extern void func_ov084_020bf9bc(void);
extern void SelectNextOption(void);
extern void func_ov084_020bfc28(void);

void *data_ov084_020bfca0[17] = {
    (void *)InitSelectMenu,
    (void *)TeardownSceneResources,
    (void *)func_ov084_020bf9bc,
    (void *)0x00000001,
    (void *)0x000001D4,
    (void *)SelectPrevOption,
    (void *)SelectNextOption,
    NULL,
    NULL,
    (void *)func_ov084_020bfc28,
    (void *)ResetMenuCursorWithSound,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)ResetMenuCursorWithSound,
};
