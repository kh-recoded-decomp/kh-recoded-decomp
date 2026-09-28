#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x1340];
    void (*enterCallback)(void);
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern void func_ov001_02072178(s32 value);
extern void func_ov001_020720cc(s32 enable);
extern void func_ov001_0207a89c(s32 value);
extern void func_ov001_02077b90(s32 value, s32 flag);

void RunHudEnterCallback_02071fb4(void) {
    if (data_020a04a4.context->enterCallback != NULL) {
        func_ov001_02072178(-1);
        func_ov001_020720cc(0);
        func_ov001_0207a89c(1);
        func_ov001_02077b90(1, 0);
        data_020a04a4.context->enterCallback();
    }
}
