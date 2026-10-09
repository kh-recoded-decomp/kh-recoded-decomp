#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageController {
    u8 pad_00[0xc];
    s16 actorId;
} StageController;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 sequencer[0x288 - 0x1d0];
    u16 flags_0 : 5;
    u16 linkA : 1;
    u16 flags_6 : 1;
    u16 linkB : 1;
    u16 flags_8 : 4;
    u16 locked : 1;
    u16 flags_13 : 3;
    u8 pad_28a[0x290 - 0x28a];
    s32 height;
    u8 pad_294[4];
    s32 speed;
    u8 pad_29c[0x2a8 - 0x29c];
    s32 mode;
    u8 pad_2ac[0x2c4 - 0x2ac];
    s32 floor;
    u8 pad_2c8[0x334 - 0x2c8];
    s32 target;
    u8 pad_338[0x378 - 0x338];
    s32 lift;
    u8 pad_37c[0x384 - 0x37c];
    s32 velocity;
    u8 pad_388[0x39c - 0x388];
    s32 scale;
} StageActor;

typedef struct StageEvent {
    u8 pad_000[0xc];
    u8 kind;
    u8 pad_00d[3];
    s16 actorId;
    u8 pad_012[6];
    u16 auxId;
    u8 pad_01a[0x4c - 0x1a];
    s32 speed;
    u8 pad_050[0x61 - 0x50];
    u8 hasTarget;
    u8 pad_062[0x70 - 0x62];
    s32 health;
    s32 rate;
    u8 pad_078[0x1a4 - 0x78];
    s32 duration;
    s32 delay;
    s32 elapsed;
    u8 pad_1b0[0x1b8 - 0x1b0];
    u16 slot;
} StageEvent;

extern void *GetStageAuxRecord_0209c1b0(u16 id);
extern StageActor *GetStageActor_0209c040(s16 id);
extern u32 GetGlobalScaleValue_0209c3cc(void);
extern void StartStageEventKind_02092bcc(StageEvent *event, int kind);
extern int ReleaseStageSlotEntry_0209c024(int index, int slot);
extern void ZeroActorSubStruct_02092790(void *aux);
extern StageController *GetStageController_0209c120(u16 slot);
extern int FixedPointMultiply12(int left, int right);
extern int FX_Div_01ff9c84(int numer, int denom);
extern void RunOverrideTrack_020b4b9c(void *sequencer, u16 overrideId);

void UpdateStageEventTimers_02092e38(StageEvent *event)
{
    StageActor *actor;
    int damage = 0;
    void *aux = GetStageAuxRecord_0209c1b0(event->auxId);
    s32 step;
    s32 duration;
    s32 period;
    StageController *controller;
    StageActor *linked;

    actor = GetStageActor_0209c040(event->actorId);
    if (actor == NULL) {
        return;
    }
    step = GetGlobalScaleValue_0209c3cc();
    if (event->health <= 0) {
        return;
    }
    if (event->delay > 0) {
        event->delay -= step;
        if (event->delay <= 0) {
            StartStageEventKind_02092bcc(event, event->kind);
            event->delay = 0;
        }
        return;
    }
    duration = event->duration;
    if (duration >= 0) {
        duration = event->duration -= step;
        if (duration <= 0) {
            if (event->slot != 0) {
                ReleaseStageSlotEntry_0209c024(4, event->slot);
                event->slot = 0;
            }
            ZeroActorSubStruct_02092790(aux);
            event->kind = 0;
            event->elapsed = 0;
            actor->scale = 0x1000;
            actor->speed = event->speed;
            actor->locked = 0;
            return;
        }
    }
    switch (event->kind) {
    case 1:
        event->elapsed -= step;
        if (event->elapsed <= 0) {
            period = FixedPointMultiply12(event->rate, 0x280);
            if (period <= 0) {
                period = 0x1000;
            }
            period = FX_Div_01ff9c84(0xf0000, period);
            if (period % 0x1000 != 0) {
                period = (period / 0x1000 + 1) * 0x1000;
            }
            damage = 0x1000;
            event->elapsed = period;
        }
        break;
    case 3:
        if (0x1c2000 - duration > 0x1e000) {
            event->elapsed -= step;
            if (event->elapsed <= 0.0) {
                event->elapsed = 0;
                if (actor->linkA || actor->linkB) {
                    damage = FixedPointMultiply12(event->rate, 0x200);
                    event->duration = 0;
                    event->elapsed = 0;
                }
            }
            controller = GetStageController_0209c120(event->slot);
            if (controller != NULL) {
                linked = GetStageActor_0209c040(controller->actorId);
                if (linked != NULL) {
                    linked->linkA = actor->linkA;
                    linked->linkB = actor->linkB;
                    if (actor->linkA || actor->linkB) {
                        RunOverrideTrack_020b4b9c(linked->sequencer, 4);
                    }
                }
            }
        }
        break;
    case 4:
        if (event->hasTarget && (actor->target == 0 || actor->mode == 0)) {
            actor->lift -= 0x52;
        }
        if (actor->velocity < 0 && actor->floor <= actor->height) {
            event->duration = 0;
            event->elapsed = 0;
        }
        break;
    case 0:
    case 2:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    if (damage != 0) {
        event->health -= damage;
        if (event->health <= 0) {
            event->health = 0x1000;
        }
    }
}
