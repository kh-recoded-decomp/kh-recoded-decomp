#include "nitro/types.h"

extern void func_01ff869c(const void *src, void *dst, u32 size);

void G3X_SetToonTable_02006bf0(const u16 *toonTable)
{
    func_01ff869c(toonTable, (void *)0x04000380, 0x40);
}
