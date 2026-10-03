#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct Actor {
    u8 pad_000[0x9ac];
    u64 flags;
    u8 player;
    u8 pad_9b5[0xa51 - 0x9b5];
    u8 guarding;
} Actor;

typedef struct {
    u8 pad_00[0x14];
    int playerIndex;
} SceneOwner;

typedef struct {
    u8 pad_00[8];
    s32 soundId;
    u8 pad_0c[0x30];
    s32 result;
    u8 pad_40[0x3c];
    s16 *groupId;
    u8 pad_80[8];
    s32 timer;
    void *cameraPath;
} SceneTask;

extern Actor *GetBoundedEntryField_0206db5c(int index);
extern void func_ov052_020d1170(Actor *actor, int mode);
extern int GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern void CameraPath_Start_020c2f44(void *path);

s32 BeginGuardIntroScene_020d8100(SceneOwner *owner, SceneTask *task, u32 *errorCode)
{
    Actor *actor = GetBoundedEntryField_0206db5c(owner->playerIndex);
    MarkerRequest request;

    actor->guarding = 0;
    actor->flags |= 0x40;
    *errorCode = 0x18;
    func_ov052_020d1170(actor, 0);
    GetLinkedAngleOffset_020ceb7c(actor);
    func_ov021_020a8ab4(&request);
    request.id = actor->player;
    request.layer = 1;
    request.angle = 0x8000;
    request.hidden = 0;
    request.soundId = task->soundId;
    request.delay = 0;
    func_ov021_020a8ca0(&request, *task->groupId);
    task->timer = 0;
    CameraPath_Start_020c2f44(task->cameraPath);
    return task->result;
}
