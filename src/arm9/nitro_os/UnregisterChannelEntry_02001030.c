#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s32 index;
    u32 value;
} ActiveEntryState;

typedef struct ChannelSlot {
    u32 inUse;
    char name[0x10];
    u32 kind;
    struct ChannelSlot *next;
    struct ChannelSlot *prev;
} ChannelSlot;

extern u32 data_020569d8[];
extern ChannelSlot data_020569e0[4][4];
extern ActiveEntryState g_activeEntry_020569cc;

extern int String_CompareBounded_020220bc(const char *s1, const char *s2, unsigned n);
extern u32 UnlinkNodeIrqSafe_02000f34(u32 listHead, u32 irqMask, ChannelSlot *node);

void UnregisterChannelEntry_02001030(u32 irqMask, const char *name, int channel)
{
    u32 *heads = data_020569d8;
    ChannelSlot *slot = data_020569e0[channel];
    int i;

    for (i = 0; i < 4; i++) {
        if (String_CompareBounded_020220bc(slot[i].name, name, 0x10) == 0 && slot[i].inUse != 0) {
            slot = &slot[i];
            break;
        }
    }
    if (i == 4) {
        return;
    }
    heads[channel] = UnlinkNodeIrqSafe_02000f34(heads[channel], irqMask, slot);
    if (g_activeEntry_020569cc.index == channel) {
        g_activeEntry_020569cc.value = heads[channel];
    }
}
