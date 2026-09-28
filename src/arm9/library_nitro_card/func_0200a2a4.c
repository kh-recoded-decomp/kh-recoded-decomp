#include "nitro/types.h"

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_02002aa8(void *queue);

int func_0200a2a4(int object, int result) {
    u32 state;
    u32 flags;

    if (result == 0x100) {
        state = func_02004938();
        flags = *(u32 *)(object + 0xc);
        while ((flags & 8) == 0) {
            func_02002aa8((void *)(object + 0x18));
            flags = *(u32 *)(object + 0xc);
        }
        func_0200494c(state);
        result = *(int *)(object + 0x14);
        *(u32 *)(object + 0xc) = *(u32 *)(object + 0xc) & 0xfffffff7;
    }
    return result;
}
