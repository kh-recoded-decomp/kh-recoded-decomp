#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GlideActor GlideActor;

struct GlideActor {
    u8 pad_000[0x1f8];
    void (*notifyLanding)(GlideActor *actor, int landed, int arg);
    void (*notifyDash)(GlideActor *actor, int arg);
    u8 pad_200[0x234 - 0x200];
    u32 bodyFlags;
    u8 pad_238[0x760 - 0x238];
    int speed;
    u8 pad_764[0x768 - 0x764];
    int grounded;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 player;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 velocity;
    VecFx32 push;
    u8 pad_9e0[0x10ec - 0x9e0];
    void (*changeMode)(GlideActor *actor, int mode);
};

extern void *func_ov001_0206db78(int player);
extern u32 GetPlayerEntryCount_02050050(int player, u32 id);
extern void ComputeRootMotionDelta_020ce9d4(GlideActor *actor, VecFx32 *out);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern BOOL AlarmCallback_020a7504(void *self);
extern BOOL HasFlagsAt0xc_020a751c(void *holder, u16 mask);

void UpdateGlideLanding_020caed4(GlideActor *actor)
{
    void *source = func_ov001_0206db78(actor->player);
    BOOL fast = FALSE;
    fx32 scale = 0x1000;
    VecFx32 delta;

    if (GetPlayerEntryCount_02050050(actor->player, 10) > 1) {
        scale = 0x1333;
    }
    ComputeRootMotionDelta_020ce9d4(actor, &delta);
    ScaleVecFx32_01ffafb4(scale, &delta, &delta);
    actor->velocity.x += delta.x;
    actor->velocity.z += delta.z;
    if (!(actor->bodyFlags & 4)) {
        BOOL moving = TRUE;
        BOOL horizontal = TRUE;
        if (actor->push.x == 0 && actor->push.y == 0) {
            horizontal = FALSE;
        }
        if (!horizontal && actor->push.z == 0) {
            moving = FALSE;
        }
        if (moving) {
            actor->velocity.x += actor->push.x;
            actor->velocity.z += actor->push.z;
            if (actor->velocity.y < 0) {
                actor->changeMode(actor, 4);
            }
            return;
        }
        actor->changeMode(actor, 4);
        return;
    }
    if (actor->speed >= 0x9000 && !(actor->stateFlags & 2) && AlarmCallback_020a7504(source)
        && HasFlagsAt0xc_020a751c(source, 0x800)) {
        actor->stateFlags |= 2;
    }
    if (actor->stateFlags & 2) {
        if (actor->speed >= 0xf000) {
            fast = TRUE;
        }
    } else {
        if (AlarmCallback_020a7504(source) && actor->speed >= 0xf000) {
            fast = TRUE;
        }
        if (actor->speed >= 0x12000) {
            fast = TRUE;
        }
    }
    if (actor->grounded != 0 || fast) {
        if (actor->stateFlags & 2) {
            actor->changeMode(actor, 8);
            if (actor->notifyDash != NULL) {
                actor->notifyDash(actor, 0);
            }
        } else {
            actor->changeMode(actor, 1);
            if (fast) {
                if (actor->notifyLanding != NULL) {
                    actor->notifyLanding(actor, 1, -1);
                }
            } else if (actor->notifyLanding != NULL) {
                actor->notifyLanding(actor, 0, -1);
            }
        }
    }
}
