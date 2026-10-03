#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x10];
    s32 markerIndex;
} MarkerConfig;

typedef struct {
    u8 pad_00[0x14];
    VecFx32 target;
} SubModeView;

typedef struct {
    fx32 minX;
    fx32 maxX;
    fx32 maxY;
    fx32 minY;
} ViewBounds;

typedef struct {
    u8 pad_00[2];
    u16 lives;
} ActorStats;

typedef struct EscapeActor EscapeActor;
typedef void (*ActorCallback)(EscapeActor *actor, int value);

struct EscapeActor {
    u8 pad_000[0x1d4];
    ActorStats *stats;
    u8 pad_1d8[0x200 - 0x1d8];
    ActorCallback onEscape;
    u8 pad_204[0x210 - 0x204];
    ActorCallback onFlash;
    u8 pad_214[0x9ac - 0x214];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0xa00 - 0x9b5];
    VecFx32 homePos;
    u8 pad_a0c[0x10ec - 0xa0c];
    ActorCallback setState;
    u8 pad_10f0[0x1108 - 0x10f0];
    u8 hitState[4];
};

extern MarkerConfig data_ov030_020bd004;
extern VecFx32 *func_ov052_020ceb54(EscapeActor *actor);
extern SubModeView *func_ov021_020af5f4(void);
extern ViewBounds *func_ov042_020bd590(void);
extern BOOL func_ov001_020645c8(int flagId);
extern void ClearFlagAndField0x144_020ab83c(void *obj);
extern void ActorSlot_UnlinkByIndex_02035c28(int index);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern fx32 ScaleValueByPercentField_020a7650(EscapeActor *actor, fx32 value);
extern BOOL AddClampedHealth_020a75ec(EscapeActor *actor, int delta);
extern MarkerConfig g_markerReset_020bd004;
extern void func_ov030_020bb468(MarkerConfig *config);
extern void FieldMenu_FocusEntryById_02078800(int id);

BOOL CheckCarriedActorEscape_020bbf78(EscapeActor *actor)
{
    VecFx32 spawnPos;
    MarkerRequest request;
    VecFx32 *pos = func_ov052_020ceb54(actor);
    SubModeView *view = func_ov021_020af5f4();
    ViewBounds *bounds = func_ov042_020bd590();
    BOOL escaped;
    fx32 damage;

    escaped = FALSE;
    spawnPos = actor->homePos;
    if (actor->stats->lives == 0 || func_ov001_020645c8(0x3625)) {
        return FALSE;
    }
    if (pos->y <= view->target.y + bounds->minY - 0x3000 && !func_ov001_020645c8(0x3ee3)) {
        spawnPos.y = view->target.y + bounds->minY;
        escaped = TRUE;
    } else if (view->target.x + (bounds->maxX + 0x1800) < pos->x) {
        spawnPos.x = view->target.x + bounds->maxX;
        escaped = TRUE;
    } else if (view->target.x + (bounds->minX - 0x1800) > pos->x) {
        spawnPos.x = view->target.x + bounds->minX;
        escaped = TRUE;
    }
    if (escaped) {
        ClearFlagAndField0x144_020ab83c(actor->hitState);
        ActorSlot_UnlinkByIndex_02035c28(actor->entryId);
        func_ov021_020a8ab4(&request);
        request.id = actor->entryId;
        request.unk_25 = 0;
        request.unk_24 = 0;
        request.prevIndex = data_ov030_020bd004.markerIndex;
        request.index = 0;
        request.pos = spawnPos;
        request.pos.z += 0x1000;
        func_ov021_020a8ca0(&request, func_ov001_0206db8c(6));
        damage = ScaleValueByPercentField_020a7650(actor, 0x14000);
        if (damage < 0x1000) {
            damage = 0x1000;
        }
        AddClampedHealth_020a75ec(actor, (s16)-(damage >> 12));
        if (actor->stats->lives == 0) {
            return escaped;
        }
        func_ov030_020bb468(&g_markerReset_020bd004);
        actor->flags |= 0x20000;
        actor->flags |= 0x40000;
        FieldMenu_FocusEntryById_02078800(-1);
        if (actor->onEscape != NULL) {
            actor->onEscape(actor, 0);
        }
        if (actor->onFlash != NULL) {
            actor->onFlash(actor, 0xbffe);
        }
        actor->setState(actor, 0x1d);
    }
    return escaped;
}
