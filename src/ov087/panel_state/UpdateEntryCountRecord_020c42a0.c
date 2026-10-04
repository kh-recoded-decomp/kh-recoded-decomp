#include "nitro/types.h"

extern int GetPlayerEntryCount_02050050(int player, u32 id);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

BOOL UpdateEntryCountRecord_020c42a0(void)
{
    u32 count = GetPlayerEntryCount_02050050(0, 9);

    if (!IsPlayerEntryFlagSet_02050014(0, 9)) {
        return FALSE;
    }
    if (count > ReadSessionPackedBits_02064574(0x1a42, 3)) {
        WriteSessionPackedBits_0206459c(0x1a42, 3, count);
        return count != 1;
    }
    return FALSE;
}
