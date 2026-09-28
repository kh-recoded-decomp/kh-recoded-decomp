#include "nitro/types.h"

extern void func_0202eb84(void *object, s32 sourceA, s32 sourceB, s32 flag, void *extra);

void func_0202ed80(u8 *object, s32 value, s32 sourceB, void *extra) {
    *(s32 *)(object + 0x74) = value;
    func_0202eb84(object, 0, sourceB, 1, extra);
}
