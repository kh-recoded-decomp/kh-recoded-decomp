#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x9ac];
    u64 flags;
} BossEntity;

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    u8 pad_00[0x3c];
    int nextState;
    u8 pad_40[0x44];
    u8 cameraPath[0x70];
    int introActive;
} SceneObject;

extern BossEntity *GetBoundedEntryField_0206db5c(int index);
extern void RunHudEnterCallback_02071fb4(void);
extern void CameraPath_Start_020c2f44(void *path);
extern void ApplyTimeScaledSpeed_020c7d28(BossEntity *entity, int speed);

int StartOv067BossIntro_020d8120(SceneOwner *owner, SceneObject *obj, int *wait)
{
    BossEntity *entity = GetBoundedEntryField_0206db5c(owner->player);

    obj->introActive = 1;
    entity->flags |= 0x1000000;
    entity->flags |= 0x20000000;
    RunHudEnterCallback_02071fb4();
    CameraPath_Start_020c2f44(obj->cameraPath);
    ApplyTimeScaledSpeed_020c7d28(entity, 0x1666);
    entity->flags |= 0x40;
    *wait = 0x18;
    return obj->nextState;
}
