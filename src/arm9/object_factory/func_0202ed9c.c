#include "nitro/types.h"

extern void func_0202eb84(void *object, s32 sourceA, s32 sourceB, s32 flag, void *extra);

void func_0202ed9c(u8 *object, s32 value, s32 sourceA, void *extra) {
    *(s32 *)(object + 0x74) = value;
    func_0202eb84(object, sourceA, 0, 1, extra);
}
