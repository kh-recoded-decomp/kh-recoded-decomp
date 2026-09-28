#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 unk_bits0 : 9;
    u32 flag9 : 1;
    u32 unk_bits10 : 22;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

BOOL IsHudFlag9Set_02072884(void) {
    if (data_020a04a4.context->flag9 == 1) {
        return TRUE;
    }
    return FALSE;
}
