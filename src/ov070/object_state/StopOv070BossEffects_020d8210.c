#include "nitro/types.h"

typedef struct BossEntity BossEntity;

struct BossEntity {
    u8 pad_000[0x204];
    void (*onSignal)(BossEntity *entity, int signal);
};

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    int active;
    u8 pad_04[4];
    int handle;
    u8 pad_0c[0x18];
} EffectSlot;

typedef struct {
    u8 pad_00[0x40];
    u8 running;
    u8 pad_41[0xf];
    s16 loopEmitter;
    s16 slotEmitter;
    u8 pad_54[4];
    int loopHandle;
    u8 pad_5c[4];
    EffectSlot slots[10];
} SceneObject;

extern BossEntity *GetBoundedEntryField_0206db5c(int index);
extern void StopAndClearSoundEmitter_020a8e14(int emitter, int handle);
extern void Camera_ChangeModeFromCurrentView_020c1014(int mode);

void StopOv070BossEffects_020d8210(SceneOwner *owner, SceneObject *obj)
{
    BossEntity *entity = GetBoundedEntryField_0206db5c(owner->player);
    int i;

    obj->running = 0;
    if (obj->loopHandle >= 0) {
        StopAndClearSoundEmitter_020a8e14(obj->loopEmitter, obj->loopHandle);
        obj->loopHandle = -1;
    }
    for (i = 0; i < 10; i++) {
        EffectSlot *slot = &obj->slots[i];
        if (slot->active) {
            slot->active = 0;
            StopAndClearSoundEmitter_020a8e14(obj->slotEmitter, slot->handle);
            slot->handle = -1;
        }
    }
    if (entity->onSignal != NULL) {
        entity->onSignal(entity, 0x1f);
    }
    Camera_ChangeModeFromCurrentView_020c1014(0);
}
