#include "nitro/types.h"

extern int data_ov086_020c2340[];
extern BOOL func_ov001_020645c8(u32 flagId);
extern int func_ov086_020bf540(int entryIndex);

int SumUnlockedGroupEntryCounts_020bf5d8(int groupIndex)
{
    int total;
    int firstEntry;
    int i;
    int entryCount;
    int entryIndex;

    firstEntry = 0;
    total = 0;

    for (i = 0; i < groupIndex; i++) {
        firstEntry += data_ov086_020c2340[i];
    }
    entryCount = data_ov086_020c2340[groupIndex];
    for (i = 0; i < entryCount; i++) {
        entryIndex = firstEntry + i;
        if (func_ov001_020645c8(entryIndex + 0x581)) {
            total += func_ov086_020bf540(entryIndex);
        }
    }
    return total;
}
