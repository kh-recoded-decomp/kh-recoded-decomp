#include "nitro/types.h"

typedef struct Ov024Context {
    u8 pad_00[8];
    void *handle;
} Ov024Context;

extern Ov024Context *g_context_020b7520;
extern void func_ov027_020b9b94(void *handle, int value);

void func_ov024_020b65c8(int value) {
    func_ov027_020b9b94(g_context_020b7520->handle, value);
}
