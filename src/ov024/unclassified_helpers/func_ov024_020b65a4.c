#include "nitro/types.h"

typedef struct Ov024Context {
    u8 pad_00[8];
    void *handle;
} Ov024Context;

typedef struct Ov024State {
    Ov024Context *context;
    int pendingTeardown;
} Ov024State;

extern Ov024State g_state_020b7520;
extern void func_ov027_020b9a74(void *handle, int value);
extern void func_ov024_020b5dc0(void);

void func_ov024_020b65a4(int value) {
    func_ov027_020b9a74(g_state_020b7520.context->handle, value);
    if (g_state_020b7520.pendingTeardown != 0) {
        func_ov024_020b5dc0();
        g_state_020b7520.pendingTeardown = 0;
    }
}
