#include "nitro/types.h"

typedef struct FieldObject FieldObject;

typedef struct FieldObjectVtbl {
    u8 pad_00[0x30];
    BOOL (*isLocked)(FieldObject *object);
} FieldObjectVtbl;

struct FieldObject {
    u32 unk_00;
    FieldObjectVtbl *vtbl;
};

typedef struct AreaDef {
    u8 pad_00[5];
    u8 objectCount;
    u8 pad_06[0x12];
    u16 *objectIds;
} AreaDef;

typedef struct AreaTracker {
    u8 pad_00[3];
    s8 objectListId;
    u8 pad_04[0xc];
    AreaDef *areas;
    u8 pad_14[0xe];
    s8 currentArea;
    s8 previousArea;
} AreaTracker;

typedef struct FieldState {
    u8 pad_00[0x40];
    AreaTracker tracker;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern u32 func_ov001_02087214(void);
extern FieldObject *func_ov001_0208635c(u32 list, u16 objectId);
extern void func_ov019_020a3588(FieldObject *object, BOOL visible);

void SwitchAreaObjects_020bc650(void)
{
    AreaTracker *tracker;
    u32 list;
    AreaDef *area;
    int objectIndex;
    FieldObject *object;
    int previousArea;

    tracker = &data_ov035_020bc4e0->tracker;
    if (tracker->objectListId < 0) {
        return;
    }
    list = func_ov001_02087214();
    previousArea = tracker->previousArea;
    if (tracker->currentArea == previousArea) {
        return;
    }
    if (previousArea >= 0) {
        area = &tracker->areas[previousArea];
        for (objectIndex = 0; objectIndex < area->objectCount; objectIndex++) {
            object = func_ov001_0208635c(list, area->objectIds[objectIndex]);
            if ((object->vtbl->isLocked != NULL ? object->vtbl->isLocked(object) : FALSE) == FALSE) {
                func_ov019_020a3588(object, FALSE);
            }
        }
    }
    if (tracker->currentArea >= 0) {
        area = &tracker->areas[tracker->currentArea];
        for (objectIndex = 0; objectIndex < area->objectCount; objectIndex++) {
            object = func_ov001_0208635c(list, area->objectIds[objectIndex]);
            if ((object->vtbl->isLocked != NULL ? object->vtbl->isLocked(object) : FALSE) == FALSE) {
                func_ov019_020a3588(object, TRUE);
            }
        }
    }
}
