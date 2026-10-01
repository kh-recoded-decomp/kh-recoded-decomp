#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    s8 inUse;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[0x132];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
    s16 groupId;
    u8 pad_0a[0x02];
    BOOL fixedSlots;
    NNSFndLink link;
} EntryGroup;

typedef struct {
    BOOL initialized;
    NNSFndList groupList;
    s32 groupCount;
    u16 nextGroupId;
} EntryRegistry;

typedef struct {
    int resourceId;
    const char *animationName;
    s32 slotCount;
    const char *modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

extern BOOL g_registryInitialized_020b5608;
extern EntryRegistry g_entryRegistry_020b5608;
extern const char data_ov021_020b51ec[];
extern const char data_ov021_020b51f4[];
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, void *object);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void func_ov021_020a81e4(EntrySlot *slot, const char *modelName, const char *animationName);

int func_ov021_020a89a8(EntryGroupDesc *desc)
{
    char modelBuffer[0x81];
    char animationBuffer[0x7F];
    EntryRegistry *registry;
    EntryGroup *group;
    const char *modelName;
    const char *animationName;
    int slotIndex;

    if (g_registryInitialized_020b5608 == FALSE) {
        return -1;
    }
    registry = &g_entryRegistry_020b5608;
    group = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(EntryGroup));
    group->fixedSlots = desc->fixedSlots;
    group->slotCount = desc->slotCount;
    group->slots = NNSi_FndAllocFromDefaultHeap_0202a178(group->slotCount * sizeof(EntrySlot));
    group->groupId = registry->nextGroupId;
    modelName = desc->modelName;
    if (modelName == NULL) {
        modelName = modelBuffer;
        OS_SPrintf_02002428(modelBuffer, data_ov021_020b51ec, desc->resourceId);
        animationName = animationBuffer;
        OS_SPrintf_02002428(animationBuffer, data_ov021_020b51f4, desc->resourceId);
    } else {
        animationName = desc->animationName;
    }
    for (slotIndex = 0; slotIndex < group->slotCount; slotIndex++) {
        func_ov021_020a81e4(&group->slots[slotIndex], modelName, animationName);
    }
    AppendIntrusiveListObject_020128d0(&registry->groupList, group);
    registry->groupCount++;
    if (registry->nextGroupId < 0xffff) {
        registry->nextGroupId++;
    } else {
        registry->nextGroupId = 0;
    }
    return group->groupId;
}
