#include "nitro/types.h"

extern void func_01ff8830(void *dst, int value, int size);

void ResetRecordState_0200af10(void *record) {
    func_01ff8830(record, 0, 0x5c);
    *(u32 *)((u8 *)record + 0x10) = 0;
    *(u32 *)((u8 *)record + 0xc) = 0;
}
