#ifndef OV001_STAGE_MOTION_STATE_H
#define OV001_STAGE_MOTION_STATE_H

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

/* Established flag and motion fields of a partial DS stage-manager view.
 * Other subsystems use their own views of the intervening storage; this
 * padded view does not establish a complete allocation size. */
typedef struct StageMotionManager {
    u32 flags;
    u8 pad00004[0x210 - 4];
    StageMotionGroup *groups;
    u8 pad00214[0x18f5c - 0x214];
    void (*setMotionMode)(StageMotionRecord *motion, int mode, int argument);
} StageMotionManager;

typedef char StageMotionGroupMustBe456Bytes[
    sizeof(StageMotionGroup) == 0x1c8 ? 1 : -1];

extern StageMotionManager *gStageManager;
extern StageObjectMotionRange *GetStageObjectHandle(u16 id);
extern StageMotionRecord *GetStageMotionRecord(u16 id);
StageMotionManager *GetStageManager(void);

#endif
