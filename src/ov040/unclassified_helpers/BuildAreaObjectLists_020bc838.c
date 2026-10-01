#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject FieldObject;

typedef struct FieldObjectVtbl {
    u8 pad_00[0x30];
    BOOL (*isLocked)(FieldObject *object);
} FieldObjectVtbl;

struct FieldObject {
    u32 unk_00;
    FieldObjectVtbl *vtbl;
    u8 pad_08[0x30];
    VecFx32 position;
};

typedef struct ObjectList {
    u8 pad_00[0x3e];
    u16 objectCount;
} ObjectList;

typedef struct AreaDef {
    u8 pad_00[4];
    u8 clearedCount;
    u8 objectCount;
    u8 pad_06[0x12];
    u16 *objectIds;
} AreaDef;

typedef struct AreaTracker {
    u8 pad_00[2];
    u8 areaCount;
    s8 objectListId;
    u8 pad_04[0xc];
    AreaDef *areas;
    u8 pad_14[0x10];
    u16 *objectIdPool;
} AreaTracker;

typedef struct FieldState {
    u8 pad_00[0x40];
    AreaTracker tracker;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern ObjectList *func_ov001_02087214(void);
extern FieldObject *func_ov001_02087224(int listId, int objectIndex);
extern s8 func_ov040_020bd9fc(VecFx32 *position);
extern void SetLinkedCallbackId_020a3580(FieldObject *object, s8 id);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff869c(const void *src, void *dest, u32 size);

void BuildAreaObjectLists_020bc838(void)
{
    AreaTracker *tracker;
    ObjectList *list;
    int poolUsed;
    int areaIndex;
    int objectIndex;
    FieldObject *object;
    s8 area;
    u16 *objectIds;
    VecFx32 position;

    tracker = &data_ov035_020bc4e0->tracker;
    if (tracker->objectListId < 0) {
        return;
    }
    list = func_ov001_02087214();
    poolUsed = 0;
    for (areaIndex = 0; areaIndex < tracker->areaCount; areaIndex++) {
        tracker->areas[areaIndex].objectIds = NNSi_FndAllocFromDefaultHeapEx_0202a19c(list->objectCount * sizeof(u16), -4);
        tracker->areas[areaIndex].objectCount = 0;
    }
    for (objectIndex = 0; objectIndex < list->objectCount; objectIndex++) {
        object = func_ov001_02087224(tracker->objectListId, objectIndex);
        position = object->position;
        position.y += 0x800;
        area = func_ov040_020bd9fc(&position);
        tracker->areas[area].objectIds[tracker->areas[area].objectCount] = objectIndex;
        tracker->areas[area].objectCount++;
        if ((object->vtbl->isLocked != NULL ? object->vtbl->isLocked(object) : FALSE) == FALSE) {
            tracker->areas[area].clearedCount++;
        }
        SetLinkedCallbackId_020a3580(object, area);
    }
    for (areaIndex = 0; areaIndex < tracker->areaCount; areaIndex++) {
        objectIds = tracker->areas[areaIndex].objectIds;
        if (tracker->areas[areaIndex].objectCount != 0) {
            func_01ff869c(objectIds, &tracker->objectIdPool[poolUsed], tracker->areas[areaIndex].objectCount * sizeof(u16));
            tracker->areas[areaIndex].objectIds = &tracker->objectIdPool[poolUsed];
            poolUsed += tracker->areas[areaIndex].objectCount;
        } else {
            tracker->areas[areaIndex].objectIds = NULL;
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(objectIds);
    }
}
