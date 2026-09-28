#include "nitro/types.h"

extern void func_02017910(u32 ptr, u32 word0, u32 arg1, u32 arg2, u32 arg3, u16 arg4);

void ForwardInnerPayload_020018e4(u32 *obj, u32 arg1, u32 arg2, u32 arg3, u16 arg4) {
    func_02017910(obj[8] + 0xc, *obj, arg1, arg2, arg3, arg4);
}
