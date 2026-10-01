#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    s8 inUse;
    u8 pad_01[0x137];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
    s16 groupId;
    u8 pad_0a[0x02];
    BOOL fixedSlots;
    NNSFndLink link;
} EntryGroup;

extern BOOL g_registryInitialized_020b5608;
extern EntryGroup *func_ov021_020a8810(int groupId);
extern void func_ov021_020a84bc(EntrySlot *slot, u8 *request);

int func_ov021_020a8ca0(u8 *request, int groupId)
{
    EntryGroup *group;
    EntrySlot *slot;
    int slotIndex;

    if (g_registryInitialized_020b5608 == FALSE) {
        return -1;
    }
    group = func_ov021_020a8810(groupId);
    if (group == NULL) {
        return -1;
    }
    if (group->fixedSlots == FALSE) {
        int slotCount = group->slotCount;
        for (slotIndex = 0; slotIndex < slotCount; slotIndex++) {
            slot = &group->slots[slotIndex];
            if (group->slots[slotIndex].inUse == 0) {
                break;
            }
        }
        if (slotIndex == slotCount) {
            return -1;
        }
    } else {
        slotIndex = request[0];
        if (group->slotCount < 3 && slotIndex > 0) {
            slotIndex--;
        }
        slot = &group->slots[slotIndex];
    }
    func_ov021_020a84bc(slot, request);
    return slotIndex;
}
