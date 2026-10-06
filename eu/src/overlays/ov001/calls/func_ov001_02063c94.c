#include "nitro/types.h"

extern u32 GetBoundedEntryField();
extern u32 SetClampedCursor();

void func_ov001_02063c94(void) {
    s32 entry = GetBoundedEntryField(0);
    SetClampedCursor(entry, *(u16 *)(*(s32 *)(entry + 0x1d4) + 4));
}
