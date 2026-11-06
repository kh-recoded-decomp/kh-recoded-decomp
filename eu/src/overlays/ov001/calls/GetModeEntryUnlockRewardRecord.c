#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

int GetModeEntryUnlockRewardRecord(int index) {
    if (index < *(int *)(gFieldEntryPoolManager + 0x1c0)) {
        return *(int *)(gFieldEntryPoolManager + 0x1c4) + index * 6;
    }
    return 0;
}
