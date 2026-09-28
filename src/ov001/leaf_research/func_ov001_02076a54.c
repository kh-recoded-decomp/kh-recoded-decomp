#include "nitro/types.h"

extern void func_01ff878c(void *dst, void *src, u32 size);
extern void func_0200160c(void *obj, u32 arg1, u32 arg2, u32 arg3, u32 arg4, void *data, void *callback, u32 arg5);
extern void *func_ov001_020711c8(void);
extern void *func_ov027_020ba2a8(void *records, u32 index);

void func_ov001_02076a54(u32 base, void *records, u32 index)
{
    void *payload;
    void *callback;

    func_01ff878c(*(void **)(base + 0xe4), *(void **)(*(u32 *)(base + index * 4 + 0x74) + 0x24), 0x200);
    payload = func_ov027_020ba2a8(records, index);
    callback = func_ov001_020711c8();
    func_0200160c((void *)(base + 0x34), 0, 4, 4, 0, payload, callback, 0x38);
}
