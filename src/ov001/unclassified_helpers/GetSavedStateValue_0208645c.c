#include "nitro/types.h"

typedef struct SavedStateOwner
{
    u8 pad_00[0x44];
    u16 bitOffset;
    u8 bitCount;
} SavedStateOwner;

extern u32 func_ov001_02064574(int bitOffset, u32 bitCount);

u16 GetSavedStateValue_0208645c(SavedStateOwner *owner)
{
    return (func_ov001_02064574(owner->bitOffset, owner->bitCount) & 0xFFFE) >> 1;
}
