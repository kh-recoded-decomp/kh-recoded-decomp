#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor, int state);

typedef struct ActorStats {
    u16 pad_00;
    u16 hp;
    u16 maxHp;
} ActorStats;

typedef struct RespawnPoint {
    fx32 heightScale;
    u8 pad_04[0x14 - 0x4];
    VecFx32 position;
} RespawnPoint;

struct Actor {
    u8 pad_0000[0x1d4];
    ActorStats *stats;
    u8 pad_01d8[0x230 - 0x1d8];
    void *model;
    u8 pad_0234[0x934 - 0x234];
    s32 mode : 8;
    s32 modeRest : 24;
    u8 pad_0938[0x944 - 0x938];
    int state;
    u8 pad_0948[0x970 - 0x948];
    VecFx32 moveVelocity;
    u8 pad_097c[0x1808 - 0x97c];
    ActorStateFunc setState;
};

extern const VecFx32 data_02053438;
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern BOOL AddClampedHealth_020a75ec(Actor *actor, s16 delta);
extern fx32 GetCameraToTargetDistance_020bca30(void);
extern RespawnPoint *func_ov021_020af5f4(void);
extern int FixedPointMultiply12(int left, int right);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void Actor_ExitCommandMode_020cb968(Actor *actor);
extern void FieldMenu_FocusEntryById_02078800(int id);

void Actor_HandleFallOut_020c837c(Actor *actor) {
    int damage;

    if (Actor_GetModelPosition_020cd0d8(actor)->y > -0x3000) {
        return;
    }
    damage = -(((actor->stats->maxHp << 12) / 100 * 20) >> 12);
    if (damage > -1) {
        damage = -1;
    }
    AddClampedHealth_020a75ec(actor, damage);
    if (actor->stats->hp != 0) {
        fx32 distance = GetCameraToTargetDistance_020bca30();
        RespawnPoint *respawn = func_ov021_020af5f4();
        VecFx32 pos = respawn->position;
        pos.x = Actor_GetModelPosition_020cd0d8(actor)->x;
        pos.y += FixedPointMultiply12(distance, respawn->heightScale) + 0x2000;
        Obj_SetPosition_0203569c(actor->model, &pos);
        if (actor->state != 12) {
            actor->setState(actor, 3);
        }
        actor->moveVelocity = data_02053438;
        Actor_ExitCommandMode_020cb968(actor);
        if (actor->mode != 1) {
            actor->mode = 0;
        }
    }
    FieldMenu_FocusEntryById_02078800(-1);
}
