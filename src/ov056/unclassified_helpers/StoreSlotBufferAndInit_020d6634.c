#include "nitro/types.h"

typedef struct SlotOwner {
    u8 pad_000[0x198];
    void *slotBuffer;
} SlotOwner;

extern void func_ov021_020aeb84(SlotOwner *owner, void *buffer);

void StoreSlotBufferAndInit_020d6634(SlotOwner *owner, void *buffer)
{
    owner->slotBuffer = buffer;
    func_ov021_020aeb84(owner, buffer);
}
