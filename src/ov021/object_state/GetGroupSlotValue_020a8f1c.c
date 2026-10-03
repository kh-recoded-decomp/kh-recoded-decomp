#include "nitro/types.h"

typedef struct {
    s8 inUse;
    u8 pad_01[3];
    u16 value;
    u8 pad_06[0x132];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
} EntryGroup;

extern BOOL g_registryInitialized_020b5608;
extern EntryGroup *func_ov021_020a8810(int groupId);

u16 GetGroupSlotValue_020a8f1c(int groupId, int index)
{
    EntryGroup *group;
    u16 value = 0;

    if (g_registryInitialized_020b5608 == FALSE) {
        return value;
    }
    group = func_ov021_020a8810(groupId);
    if (group != NULL) {
        value = group->slots[index].value;
    }
    return value;
}
