#include "nitro/types.h"

typedef struct EventEffect {
    int state;
    int timer;
} EventEffect;

typedef struct Entity {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 pad_9b4[0x9c0 - 0x9b4];
    int delay;
} Entity;

extern EventEffect *data_ov010_020a1dc0;

extern void func_ov010_020a0d98(EventEffect *effect);
extern void func_ov010_020a0f60(EventEffect *effect, int step);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void func_ov001_020645e8(int eventId);
extern void StartObjectEffects_020a0e6c(EventEffect *effect);
extern void func_ov010_020a0d00(EventEffect *effect);
extern void SpawnEffectAtTarget_020a1028(EventEffect *effect);
extern void Camera_ReturnFromPathView_020c2fac(void);

void Entity_UpdateEventEffect_020a18ac(Entity *entity, int step)
{
    EventEffect *effect = data_ov010_020a1dc0;

    if (effect == NULL) {
        return;
    }
    func_ov010_020a0d98(effect);
    func_ov010_020a0f60(effect, step);
    if (func_ov001_020645c8(0x3713) && effect->state == 0) {
        if (entity->delay != 0x18) {
            effect->state = 1;
            effect->timer = 0;
            StartObjectEffects_020a0e6c(effect);
        } else {
            func_ov001_020645e8(0x3713);
        }
    }
    if (effect->state != 0) {
        effect->timer += step;
        if (effect->state == 1 && effect->timer >= 0x96000) {
            func_ov010_020a0d00(effect);
        }
        if (entity->stateFlags & 0x100000020ULL) {
            func_ov010_020a0d00(effect);
            SpawnEffectAtTarget_020a1028(effect);
            Camera_ReturnFromPathView_020c2fac();
        }
    }
}
