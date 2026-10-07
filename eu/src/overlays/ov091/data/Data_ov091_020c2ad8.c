#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyMenuScene(void);
extern void InitRecordMenuScene(void);
extern void MoveEntryCursorDown(void);
extern void MoveEntryCursorUp(void);
extern void OpenSelectedEntryScene(void);
extern void TryCloseEntryMenu(void);
extern void func_ov091_020bed84(void);

u32 data_ov091_020c2bd4[36] = {
    0x00000000, 0x00000000, 0x00000078, 0x00000028,
    0x00000001, 0x00000001, 0x00000000, 0x00000001,
    0x000000E8, 0x00000029, 0x00000000, 0x00000000,
    0x00000000, 0x00000001, 0x000000E8, 0x00000039,
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x000000E8, 0x00000049, 0x00000000, 0x00000000,
    0x00000000, 0x00000001, 0x000000E8, 0x00000059,
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x000000E8, 0x00000069, 0x00000000, 0x00000000,
};

u32 data_ov091_020c2b5c[30] = {
    0x00000064, 0x00000050, 0x00000064, 0x00000064,
    0x00000064, 0x00000046, 0x00000032, 0x00000001,
    0x00000001, 0x00000001, 0x00000001, 0x00000064,
    0x00000064, 0x00000001, 0x00000001, 0x00000064,
    0x00000001, 0x00000064, 0x00000064, 0x00000064,
    0x0000000A, 0x00000064, 0x00000001, 0x00000001,
    0x00000001, 0x00000001, 0x00000001, 0x00000001,
    0x00000001, 0x00000001,
};

void *data_ov091_020c2b18[17] = {
    (void *)InitRecordMenuScene,
    (void *)DestroyMenuScene,
    (void *)func_ov091_020bed84,
    (void *)0x00000004,
    (void *)0x0000CC80,
    (void *)MoveEntryCursorUp,
    (void *)MoveEntryCursorDown,
    NULL,
    NULL,
    (void *)OpenSelectedEntryScene,
    (void *)TryCloseEntryMenu,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)TryCloseEntryMenu,
};

u32 data_ov091_020c2ad8[16] = {
    0x00000A6B, 0x0000012C, 0x00000A7C, 0x00000384,
    0x00000A8D, 0x00000384, 0x00000A9E, 0x00000258,
    0x00000AAF, 0x00000384, 0x00000AC0, 0x00000384,
    0x00000AD1, 0x00000708, 0x00000AE2, 0x00000258,
};
