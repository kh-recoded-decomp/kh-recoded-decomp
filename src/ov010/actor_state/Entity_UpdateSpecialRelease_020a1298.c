#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    s32 rate;
    void *target;
    u8 pad_1c[8];
    u8 mode;
    u8 loop;
    s16 priority;
    s16 soundId;
    s16 volume;
} TrackState;

typedef struct EventEffect {
    int state;
    int timer;
    int active;
    u8 pad_0c[4];
    int counter;
    u8 pad_14[8];
    int elapsed;
    u8 pad_20[4];
    BOOL burstStarted;
    BOOL releaseReady;
    u8 pad_2c[8];
    s16 burstGroup;
    u8 pad_36[6];
    u8 cameraState[4];
} EventEffect;

typedef struct Entity Entity;

typedef void (*EntityEventFunc)(Entity *entity, int event, int value);
typedef int (*EntityModeFunc)(Entity *entity, int mode);
typedef void (*EntityStateHandler)(Entity *entity);

struct Entity {
    u8 pad_000[0x1f8];
    EntityEventFunc onEvent;
    u8 pad_1fc[0x760 - 0x1fc];
    int chargeTime;
    u8 pad_764[4];
    void *chargeTarget;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 slot;
    u8 pad_9b5[7];
    EntityStateHandler stateHandler;
    u8 pad_9c0[8];
    VecFx32 focusPosition;
    u8 pad_9d4[0x10ec - 0x9d4];
    EntityModeFunc modeCallback;
};

extern EventEffect *data_ov010_020a1dc0;
extern const VecFx32 data_ov010_020a1d20;

extern void func_ov052_020ce9d4(Entity *entity, VecFx32 *out);
extern void func_ov021_020a8ab4(TrackState *state);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);
extern void func_ov010_020a10b8(Entity *entity);
extern void func_ov010_020a13cc(Entity *entity);
extern void func_ov001_020645dc(u32 eventId);
extern void func_ov046_020c2f44(void *cameraState);
extern void func_ov010_020a0d00(EventEffect *effect);

static inline void Vec_Set(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void Entity_UpdateSpecialRelease_020a1298(Entity *entity)
{
    EventEffect *effect = data_ov010_020a1dc0;
    TrackState request;
    VecFx32 focus;

    func_ov052_020ce9d4(entity, &focus);
    Vec_Set(&entity->focusPosition, focus.x, focus.y, focus.z);
    if (!effect->burstStarted && entity->chargeTime >= 0xe000) {
        effect->burstStarted = TRUE;
        func_ov021_020a8ab4(&request);
        request.id = entity->slot;
        request.loop = 1;
        request.angle = 0x8000;
        request.position = data_ov010_020a1d20;
        request.soundId = 0xf4;
        request.volume = 0x19;
        request.mode = 0;
        func_ov021_020a8ca0(&request, effect->burstGroup);
    }
    func_ov010_020a10b8(entity);
    if (entity->chargeTime >= 0x19000 && effect->releaseReady) {
        entity->stateHandler = func_ov010_020a13cc;
        if (entity->onEvent != NULL) {
            entity->onEvent(entity, 0x18, -1);
        }
        effect->state = 3;
        effect->timer = 0;
        effect->elapsed = 0;
        func_ov001_020645dc(0x3717);
        func_ov046_020c2f44(effect->cameraState);
        effect->counter = 0;
        return;
    }
    if (entity->chargeTarget != NULL) {
        func_ov010_020a0d00(effect);
        entity->stateFlags &= ~0x01000000ULL;
        entity->modeCallback(entity, 1);
        if (entity->onEvent != NULL) {
            entity->onEvent(entity, 0, -1);
        }
    }
}
