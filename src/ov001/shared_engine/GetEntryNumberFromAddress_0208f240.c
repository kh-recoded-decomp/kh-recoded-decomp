#include "nitro/types.h"

u16 GetEntryNumberFromAddress_0208f240(u32 *base, u32 address)
{
    u16 index = (address - *base) / 12;

    return index + 1;
}
