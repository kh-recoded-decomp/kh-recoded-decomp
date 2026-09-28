#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x1344];
    void (*exitCallback)(void);
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern BOOL func_ov001_02072040(void);
extern void func_ov001_0207a89c(s32 value);
extern void func_ov001_02077b90(s32 value, s32 flag);

void RunHudExitCallback_02071fec(void) {
    if (data_020a04a4.context->exitCallback != NULL && func_ov001_02072040()) {
        data_020a04a4.context->exitCallback();
        func_ov001_0207a89c(0);
        func_ov001_02077b90(0, 0);
    }
}
