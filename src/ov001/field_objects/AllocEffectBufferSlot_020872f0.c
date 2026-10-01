#include "nitro/types.h"

typedef struct BufferSlot {
    u16 resourceId : 10;
    u16 kind : 6;
    u16 size;
    void *buffer;
} BufferSlot;

typedef struct EffectManager {
    u8 pad_000[0x138];
    BufferSlot slots[1];
} EffectManager;

typedef struct EffectEntry {
    u8 pad_00[0x3e];
    u16 resourceId;
    u8 pad_40[0x19];
    u8 slotIndex;
    u8 kind;
} EffectEntry;

extern EffectManager *data_ov001_020a04dc;

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);

void AllocEffectBufferSlot_020872f0(EffectEntry *entry, u32 size)
{
    BufferSlot *slots = data_ov001_020a04dc->slots;
    BufferSlot *slot = &slots[entry->slotIndex];

    slot->kind = entry->kind;
    slot->resourceId = entry->resourceId;
    slot->size = size;
    slot->buffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, -4);
}
