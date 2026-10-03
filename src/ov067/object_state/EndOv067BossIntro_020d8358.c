#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x9ac];
    u64 flags;
    u8 pad_9b4[0xfc8 - 0x9b4];
    u8 handle[4];
} BossEntity;

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

extern BossEntity *GetBoundedEntryField_0206db5c(int index);
extern BOOL Camera_ReturnFromPathView_020c2fac(void);
extern void ResetObjHandle_020aa4c8(void *handle);
extern void RunHudExitCallback_02071fec(void);
extern void ApplyTimeScaledSpeed_020c7d28(BossEntity *entity, int speed);
extern void ResetGaugeDisplay_020734f8(void);
extern void SetManagerEnabled_0206e160(u32 enabled);
extern void StopEntrySounds_020addcc(SceneOwner *owner, void *obj);

void EndOv067BossIntro_020d8358(SceneOwner *owner, void *obj)
{
    BossEntity *entity = GetBoundedEntryField_0206db5c(owner->player);

    Camera_ReturnFromPathView_020c2fac();
    ResetObjHandle_020aa4c8(entity->handle);
    entity->flags &= ~0x1000000ULL;
    entity->flags &= ~0x20000000ULL;
    RunHudExitCallback_02071fec();
    ApplyTimeScaledSpeed_020c7d28(entity, 0x1000);
    ResetGaugeDisplay_020734f8();
    SetManagerEnabled_0206e160(0);
    StopEntrySounds_020addcc(owner, obj);
}
