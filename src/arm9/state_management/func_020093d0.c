#include "nitro/types.h"

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_02002aa8(u32 *queue);

BOOL func_020093d0(u32 *request, int setArgs, u32 arg1, u32 arg2) {
    u32 state;
    u32 flags;

    state = func_02004938();
    flags = request[1];
    while ((flags & 4) != 0) {
        func_02002aa8(request + 0x13d);
        flags = request[1];
    }
    if (setArgs != 0) {
        request[1] = request[1] | 4;
        request[0x13b] = arg1;
        request[0x13c] = arg2;
    }
    func_0200494c(state);
    if (*(int *)*request == 0) {
        return 1;
    }
    return 0;
}
