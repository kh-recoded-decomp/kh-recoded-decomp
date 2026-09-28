#include "nitro/types.h"

extern u32 func_ov001_020711b0(void);
extern u32 func_ov027_020b8184(u32 handle, int index);
extern void InvokeCallback40_020b8268(u32 handle, u32 value);
extern u32 func_ov027_020b8390(u32 handle, int index);
extern void func_ov027_020b83e8(u32 handle, u32 value, int flag);

void func_ov035_020bc38c(void) {
    u32 handle;
    u32 value;

    handle = func_ov001_020711b0();
    value = func_ov027_020b8390(handle, 1);
    func_ov027_020b83e8(handle, value, 0);
    value = func_ov027_020b8184(handle, 5);
    InvokeCallback40_020b8268(handle, value);
}
