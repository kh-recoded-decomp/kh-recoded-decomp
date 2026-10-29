#include "nitro/types.h"

extern unsigned int UpdateSceneScroll(void);
extern void AdvanceToRoutedSlot(int entry, unsigned int value);

void ApplyRewardEntryOffset(int entry, int offset)
{
    int baseValue;

    if (entry != 0) {
        baseValue = UpdateSceneScroll();
        AdvanceToRoutedSlot(entry, baseValue + offset);
    }
}
