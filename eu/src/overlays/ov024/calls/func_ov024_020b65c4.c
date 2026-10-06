#include "nitro/types.h"

typedef struct Ov024Context {
    u8 pad_00[8];
    void *handle;
} Ov024Context;

typedef struct Ov024State {
    Ov024Context *context;
    int pendingTeardown;
} Ov024State;

extern Ov024State data_ov024_020b7540;
extern void func_ov027_020b9a94(void *handle, int value);
extern void ReleaseOverlayResourceSlots(void);

void func_ov024_020b65c4(int value) {
    func_ov027_020b9a94(data_ov024_020b7540.context->handle, value);
    if (data_ov024_020b7540.pendingTeardown != 0) {
        ReleaseOverlayResourceSlots();
        data_ov024_020b7540.pendingTeardown = 0;
    }
}
