#include "src/overlays/ov001/StageMotionState.h"

void DispatchStageObjectMotions(u16 objectId, int mode, int argument)
{
    StageObjectMotionRange *handle = GetStageObjectHandle((u16)(objectId + 1));
    u16 group;

    for (group = handle->firstGroup; group <= handle->lastGroup; group++) {
        StageMotionGroup *entry = &gStageManager->groups[group];
        if (entry->active) {
            StageMotionRecord *motion = GetStageMotionRecord(entry->motionId);
            StageMotionManager *manager = GetStageManager();

            if (manager != NULL && manager->setMotionMode != NULL) {
                manager->setMotionMode(motion, (s16)mode, argument);
            }
        }
    }
}
