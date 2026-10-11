#include "nitro/types.h"

typedef struct StageMotionRecord {
    u8 pad00[2];
    u8 state;
} StageMotionRecord;

typedef struct StageMotionGroup {
    u8 pad00[0x10];
    u16 active;
    u8 pad12[4];
    u16 motionId;
    u8 pad18[0x1c8 - 0x18];
} StageMotionGroup;

typedef struct StageObjectMotionRange {
    u8 pad00[0xa];
    u16 firstGroup;
    s16 lastGroup;
} StageObjectMotionRange;

typedef struct StageMotionManager {
    u8 pad00000[0x210];
    StageMotionGroup *groups;
    u8 pad00214[0x18f5c - 0x214];
    void (*setMotionMode)(StageMotionRecord *motion, int mode, int argument);
} StageMotionManager;

typedef char StageMotionGroupMustBe456Bytes[
    sizeof(StageMotionGroup) == 0x1c8 ? 1 : -1];

extern StageMotionManager *gStageManager_020a0508;
extern StageObjectMotionRange *GetStageObjectHandle_0209c0c4(u16 id);
extern StageMotionRecord *GetStageMotionRecord_0209c18c(u16 id);
StageMotionManager *GetStageManager_0209c3c0(void);

void DispatchStageObjectMotions_0209c6c8(u16 objectId, int mode, int argument)
{
    StageObjectMotionRange *handle = GetStageObjectHandle_0209c0c4((u16)(objectId + 1));
    u16 group;

    for (group = handle->firstGroup; group <= handle->lastGroup; group++) {
        StageMotionGroup *entry = &gStageManager_020a0508->groups[group];
        if (entry->active) {
            StageMotionRecord *motion = GetStageMotionRecord_0209c18c(entry->motionId);
            StageMotionManager *manager = GetStageManager_0209c3c0();

            if (manager != NULL && manager->setMotionMode != NULL) {
                manager->setMotionMode(motion, (s16)mode, argument);
            }
        }
    }
}
