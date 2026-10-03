#include "nitro/types.h"

typedef struct SlotCounter {
    u8 pad_00[0x3f];
    u8 count;
    u8 cursor;
} SlotCounter;

extern void func_ov021_020aafe4(SlotCounter *counter);

void ResetCountsAndSlots_020aeb6c(SlotCounter *counter)
{
    counter->cursor = 0;
    counter->count = 0;
    func_ov021_020aafe4(counter);
}
