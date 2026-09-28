#include "nitro/types.h"

typedef struct SavedStateOwner
{
    u8 pad_00[0x44];
    u16 bitOffset;
    u8 bitCount;
} SavedStateOwner;

extern u32 func_ov001_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

void SetSavedStateValue_0208647c(SavedStateOwner *owner, u16 value)
{
    WriteSessionPackedBits_0206459c(owner->bitOffset, owner->bitCount,
                                    (func_ov001_02064574(owner->bitOffset, owner->bitCount) & 0xFFFF0001) | (value << 1));
}
