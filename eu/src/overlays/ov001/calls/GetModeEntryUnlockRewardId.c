#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

int GetModeEntryUnlockRewardId(int index) {
    if (index < *(int *)(gFieldEntryPoolManager + 0x1b8)) {
        return *(int *)(gFieldEntryPoolManager + 0x1bc) + index * 2;
    }
    return 0;
}
