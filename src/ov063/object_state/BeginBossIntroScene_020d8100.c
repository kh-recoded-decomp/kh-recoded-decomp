#include "nitro/types.h"

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*playMotion)(Actor *actor, int motion, int blend);
    u8 pad_1fc[0x9ac - 0x1fc];
    u64 flags;
};

typedef struct {
    u8 pad_00[0x14];
    int playerIndex;
} SceneOwner;

typedef struct {
    u8 pad_00[0x3c];
    s32 result;
    s32 motionBase;
    s32 timer;
    s32 step;
    s32 phase;
    u8 pad_50[0xc];
    void *cameraPath;
} SceneTask;

extern Actor *GetBoundedEntryField_0206db5c(int index);
extern void UpdateFacingTowardTarget_020cec9c(Actor *actor, BOOL useEntry);
extern void CameraPath_Start_020c2f44(void *path);

s32 BeginBossIntroScene_020d8100(SceneOwner *owner, SceneTask *task, u32 *errorCode)
{
    Actor *actor = GetBoundedEntryField_0206db5c(owner->playerIndex);
    int motion;

    task->step = 0;
    task->timer = 0;
    task->phase = 0;
    UpdateFacingTowardTarget_020cec9c(actor, FALSE);
    motion = task->motionBase + 0x1e;
    if (actor->playMotion != NULL) {
        actor->playMotion(actor, motion, -1);
    }
    actor->flags |= 0x40;
    CameraPath_Start_020c2f44(task->cameraPath);
    *errorCode = 0x18;
    return task->result;
}
