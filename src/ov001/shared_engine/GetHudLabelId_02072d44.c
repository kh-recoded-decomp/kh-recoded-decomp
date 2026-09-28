#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x6ec];
    s32 labelIds[4];
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

s32 GetHudLabelId_02072d44(int labelIndex) {
    return data_020a04a4.context->labelIds[labelIndex];
}
