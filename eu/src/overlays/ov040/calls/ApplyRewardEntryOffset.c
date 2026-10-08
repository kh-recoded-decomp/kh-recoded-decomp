#include "nitro/types.h"

extern unsigned int func_ov031_020bb074(void);
extern void func_ov032_020bb034(int entry, unsigned int value);

void ApplyRewardEntryOffset(int entry, int offset)
{
    int baseValue;

    if (entry != 0) {
        baseValue = func_ov031_020bb074();
        func_ov032_020bb034(entry, baseValue + offset);
    }
}
