#include "nitro/types.h"

extern void AllocWorldNamedEntries(int count);
extern void SetWorldNamedEntryValue(int index, const u32 *value);

void ResetWorldNamedEntries(void)
{
    u32 record;
    u8 *bytes;
    int i;

    AllocWorldNamedEntries(11);
    bytes = (u8 *)&record;
    bytes[0] = 0;
    bytes[1] = 0;
    bytes[2] = 0;
    bytes[3] = 0;
    for (i = 0; i < 11; i++) {
        *(u8 *)&record = i & 0xff;
        SetWorldNamedEntryValue(i & 0xff, &record);
    }
}
