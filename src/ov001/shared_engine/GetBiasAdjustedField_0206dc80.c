#include "nitro/types.h"

extern u32 GetBoundedEntryField_0206db5c();

u16 GetBiasAdjustedField_0206dc80(void)
{
    u32 base;

    base = GetBoundedEntryField_0206db5c();
    return (u16)(*(u16 *)(base + 0x94) - 0x8000);
}
