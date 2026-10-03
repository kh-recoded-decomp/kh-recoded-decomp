#include "nitro/types.h"

typedef struct EventOwner {
    u8 pad0[2];
    u16 baseId;
} EventOwner;

typedef struct StageObject {
    u8 pad0[0x1d0];
    u16 linkType;
    u16 eventId;
} StageObject;

extern void *data_ov021_020b56a4;
extern void *GetStageEventRecord_0209c0ec(u32 id);
extern StageObject *FindStageObjectById_0209c290(u16 id);

void *ResolveEventRecordRef_020b0250(EventOwner *owner, int ref)
{
    void *record = data_ov021_020b56a4;
    StageObject *object;

    if (record != NULL) {
        switch (ref & 0xff00) {
        case 0:
            record = GetStageEventRecord_0209c0ec((u16)(owner->baseId + ref));
            if (record == NULL) {
                return NULL;
            }
            break;
        case 0xf00:
        case 0xff00:
            object = FindStageObjectById_0209c290(ref);
            if (object == NULL) {
                return NULL;
            }
            if (object->linkType != 1) {
                return NULL;
            }
            return GetStageEventRecord_0209c0ec(object->eventId);
        }
    }
    return record;
}
