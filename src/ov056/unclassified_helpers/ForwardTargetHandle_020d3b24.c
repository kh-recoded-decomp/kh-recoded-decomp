#include "nitro/types.h"

typedef struct EventTarget {
    u8 pad_00[0x84];
    void *handle;
} EventTarget;

extern void func_ov021_020aafd4(void *handle);

void ForwardTargetHandle_020d3b24(u32 unused, EventTarget *target)
{
    func_ov021_020aafd4(target->handle);
}
