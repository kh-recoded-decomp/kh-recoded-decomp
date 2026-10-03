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
    u8 pad_00[0x4c];
    s16 emitter;
    u8 pad_4e[0x33];
    s8 soundHandle;
} SceneObject;

extern BossEntity *GetBoundedEntryField_0206db5c(int index);
extern BOOL Camera_ReturnFromPathView_020c2fac(void);
extern void RunHudExitCallback_02071fec(void);
extern void StopAndClearSoundEmitter_020a8e14(int emitter, int handle);
extern void ResetGaugeDisplay_020734f8(void);
extern void SetManagerEnabled_0206e160(u32 enabled);
extern void StopEntrySounds_020addcc(SceneOwner *owner, SceneObject *obj);

void EndOv068BossIntro_020d84b4(SceneOwner *owner, SceneObject *obj)
{
    BossEntity *entity = GetBoundedEntryField_0206db5c(owner->player);
    int handle;
    int emitter;

    Camera_ReturnFromPathView_020c2fac();
    entity->flags &= ~0x1000000ULL;
    entity->flags &= ~0x20000000ULL;
    RunHudExitCallback_02071fec();
    emitter = obj->emitter;
    handle = obj->soundHandle;
    if (handle != -1) {
        StopAndClearSoundEmitter_020a8e14(emitter, handle);
        obj->soundHandle = -1;
    }
    ResetGaugeDisplay_020734f8();
    SetManagerEnabled_0206e160(0);
    StopEntrySounds_020addcc(owner, obj);
}
