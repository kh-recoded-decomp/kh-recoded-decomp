#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ObjectDef {
    u8 pad_00[0x5a];
    u8 kind;
} ObjectDef;

typedef struct TrackedObject {
    struct TrackedObject *next;
    ObjectDef *def;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 pad_33[0x20];
    s8 hidden;
} TrackedObject;

typedef struct TargetRef {
    union {
        TrackedObject *object;
        struct {
            u16 eventId;
            u16 subId;
        } event;
    } u;
    int type;
} TargetRef;

typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

typedef struct RewardQueue {
    u8 pad_000[0x60];
    TargetRef entries[16];
    fx32 timers[8];
    fx32 fades[8];
    u8 count;
    u8 capacity;
} RewardQueue;

typedef struct RewardOwner {
    u8 pad_00[4];
    s16 width;
    s16 height;
    u8 pad_08[8];
    ScreenPos screen;
    fx32 scaleX;
    fx32 scaleY;
    u8 pad_20[0x70];
    RewardQueue queue;
    u8 pad_1b4[0xc];
    int selected;
} RewardOwner;

typedef struct ActorBody {
    u8 pad_00[0x24];
    VecFx32 *position;
} ActorBody;

typedef struct ActorNode {
    u8 pad_000[0x10c];
    ActorBody body;
} ActorNode;

typedef struct Player {
    u8 pad_000[0x934];
    int mode;
} Player;

extern u16 GetCameraRollAngle_020af84c(void);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Player *player);
extern int ProjectWorldToScreenFx_0206ad34(const VecFx32 *world, ScreenPos *screen);
extern void RewardQueue_PruneOutOfRange_020cf5b4(RewardQueue *queue);
extern int FixedPointMultiply12(int a, int b);
extern TrackedObject *func_ov001_0208723c(void);
extern BOOL IsTargetInVerticalRange_020cf100(TargetRef *ref);
extern int EntryList_FindByValue_020cf41c(RewardQueue *queue, TrackedObject *object);
extern ActorNode *func_02036240(u32 actorId);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void RewardQueue_InsertScored_020cf860(const TargetRef *entry, int score, RewardOwner *owner, TargetRef *entries, int *scores, int *count);
extern u16 func_ov001_02087928(void);
extern u16 func_ov001_02087944(s32 service);
extern BOOL QueryStageEventPlacement_02087bec(u32 id, int arg, VecFx32 *position, u16 *next);
extern BOOL RewardQueue_CanAddEventHit_020cf4c8(RewardQueue *queue, u16 eventId, u16 subId);
extern void MarkerList_ProjectToScreen_020cf65c(RewardQueue *queue);

static inline TargetRef MakeObjectRef(TrackedObject *object)
{
    TargetRef key;

    key.u.object = object;
    key.type = 1;
    return key;
}

static inline TargetRef MakeEventRef(u16 eventId, u16 subId)
{
    TargetRef key;

    key.u.event.eventId = eventId;
    key.u.event.subId = subId;
    key.type = 2;
    return key;
}

static inline BOOL IsInsideView(RewardOwner *owner, const VecFx32 *pos, const ScreenPos *lo, const ScreenPos *hi)
{
    ScreenPos screen;

    if (ProjectWorldToScreenFx_0206ad34(pos, &screen) != -1 && screen.x >= lo->x && screen.x <= hi->x
        && screen.y >= lo->y && screen.y <= hi->y) {
        fx32 dy = screen.y - owner->screen.y;
        fx32 dx = screen.x - owner->screen.x;
        if (FX_Sqrt_01ff9cfc((fx32)(((s64)dx * dx + (s64)dy * dy) >> 12)) <= (hi->x - lo->x) / 2) {
            return TRUE;
        }
    }
    return FALSE;
}

void RewardQueue_GatherTargets_020cf9f8(RewardOwner *owner, Player *player)
{
    TargetRef entries[8];
    int scores[8];
    VecFx32 eventPos;
    VecFx32 pos;
    int count;
    ScreenPos hi;
    ScreenPos lo;
    TargetRef objectRef;
    TargetRef eventRef;
    ScreenPos screen;
    u16 next;

    GetCameraRollAngle_020af84c();
    pos = *Actor_GetModelPosition_020cd0d8(player);
    pos.y += 0x119a;
    pos.z -= 0x5000;
    ProjectWorldToScreenFx_0206ad34(&pos, &screen);
    screen.y += 0x8000;
    owner->screen = screen;
    RewardQueue_PruneOutOfRange_020cf5b4(&owner->queue);
    if ((s8)player->mode == 2 && owner->queue.count < owner->queue.capacity) {
        TrackedObject *object;
        u16 service;

        count = 0;
        hi = lo = owner->screen;
        hi.x += (FixedPointMultiply12(owner->width, owner->scaleX) << 12) / 2;
        hi.y += (FixedPointMultiply12(owner->height, owner->scaleY) << 12) / 2;
        lo.x -= (FixedPointMultiply12(owner->width, owner->scaleX) << 12) / 2;
        lo.y -= (FixedPointMultiply12(owner->height, owner->scaleY) << 12) / 2;
        for (object = func_ov001_0208723c(); object != NULL; object = object->next) {
            if (object->def->kind == 6 && object->hidden != -1) {
                objectRef = MakeObjectRef(object);
                if (IsTargetInVerticalRange_020cf100(&objectRef) && EntryList_FindByValue_020cf41c(&owner->queue, object) == -1) {
                    ActorBody *body = &func_02036240(object->actorId)->body;
                    VecFx32 *target = body->position;
                    if (IsInsideView(owner, target, &lo, &hi)) {
                        RewardQueue_InsertScored_020cf860(&objectRef, target->z, owner, entries, scores, &count);
                    }
                }
            }
        }
        for (service = func_ov001_02087928(); service != 0; service = func_ov001_02087944(service)) {
            u16 sub = 0;

            if (QueryStageEventPlacement_02087bec(service, 0, &eventPos, &next)) {
                do {
                    eventRef = MakeEventRef(service, sub);
                    if (IsTargetInVerticalRange_020cf100(&eventRef) && RewardQueue_CanAddEventHit_020cf4c8(&owner->queue, service, sub)) {
                        if (IsInsideView(owner, &eventPos, &lo, &hi)) {
                            RewardQueue_InsertScored_020cf860(&eventRef, eventPos.z, owner, entries, scores, &count);
                        }
                    }
                    if (sub >= next) {
                        break;
                    }
                    sub = next;
                } while (QueryStageEventPlacement_02087bec(service, sub, &eventPos, &next));
            }
        }
        if (owner->queue.count == owner->queue.capacity) {
            owner->selected = 0;
        }
    }
    MarkerList_ProjectToScreen_020cf65c(&owner->queue);
}
