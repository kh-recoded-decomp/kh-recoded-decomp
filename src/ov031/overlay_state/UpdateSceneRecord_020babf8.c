#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventTargetInfo {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct {
    s32 triggerDistance;
    s32 kind;
    u8 pad_08[0x34];
} ActiveRecord;

typedef struct {
    u8 data[0x88];
} GroupObject;

typedef struct {
    u8 hidden;
    u8 slot;
    u8 objectCount;
    u8 pad_03[0x5];
    VecFx32 position;
    u8 pad_14[0x4];
    GroupObject *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x38];
    s32 distance;
    u8 pad_3c[0x4];
    s32 stepIndex;
    s32 recordIndex;
    s32 nextRecordIndex;
    u8 pad_4c[0x4];
    ActiveRecord *records;
    u8 fadeMode;
    u8 pad_55;
    u8 activeGroupCount;
    u8 pad_57;
    u8 brightnessTarget;
    u8 brightnessBase;
    u8 pad_5a;
    u8 initialized;
    u16 nearestEvent;
    u8 pad_5e[0x2];
    u8 pad_60[0x4];
    ObjectGroup *groups;
    s32 maxDepth[9];
    u8 pad_8c[0x28];
    s32 brightness;
    u8 pad_b8[0x8];
    s32 blendTime;
    s32 blendDuration;
    s32 blendCurve;
    s32 blendFrom;
    s32 blendTo;
} OverlayState;

typedef struct {
    u8 pad_00[0x5a];
    u8 category;
} ActorInfo;

typedef struct Actor {
    struct Actor *next;
    ActorInfo *info;
    u8 pad_08[0x38];
    s32 depth;
    u8 pad_44[0xc];
    u16 flags;
} Actor;

typedef struct {
    u32 unk_00;
    int **trees;
} WorldState;

extern OverlayState *g_activeState_020bc800;
extern WorldState *func_02036230(void);
extern void ResetField44_020bbea4(void);
extern fx32 EaseProgress_0204a174(fx32 time, fx32 duration, s32 curve);
extern void ResetCameraUp_020bca50(fx32 value);
extern BOOL StageRecord_IsDefeated_02087cc4(u32 id);
extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 startIndex);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern void FindNearestStageEvent_020bab74(void);
extern void HideFieldMessageLine_0207166c(void);
extern void ShowFieldMessageLine_0207163c(u16 tickerMode, u32 tickerValue, int messageId, BOOL resetTicker);
extern BOOL QueryStageEventState_0209c758(int mode, int groupId);
extern s32 func_ov031_020bc700(void);
extern void QuadTree_RemoveObject_02033c60(int *tree, GroupObject *node);
extern Actor *func_ov001_0208723c(void);
extern BOOL TestFlagBit9_020a37e4(Actor *actor);
extern void AdvanceRecordStep_020bc554(void);
extern BOOL CanLeaveActiveRecord_020bb010(void);
extern void func_ov031_020bb5d8(void);
extern void BeginNextRecord_020bb62c(void);
extern void func_ov001_0207b49c(u32 a, u32 b, u32 c);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800) >> 12);
}

void UpdateSceneRecord_020babf8(void)
{
    ActiveRecord *record;
    fx32 t;
    s32 id;
    EventTargetInfo info;
    EventTargetInfo target;
    int i;
    BOOL advance;
    int count;
    int j;
    ObjectGroup *group;
    WorldState *world;
    Actor *actor;

    if (g_activeState_020bc800->recordIndex != -1) {
        record = &g_activeState_020bc800->records[g_activeState_020bc800->recordIndex];
    } else {
        record = NULL;
    }
    if (g_activeState_020bc800->initialized == 0) {
        func_02036230();
        g_activeState_020bc800->initialized = 1;
        ResetField44_020bbea4();
    }
    if (g_activeState_020bc800->stepIndex == -1) {
        return;
    }
    if (g_activeState_020bc800->blendTime != -1) {
        g_activeState_020bc800->blendTime += 0x1000;
        if (g_activeState_020bc800->blendTime >= g_activeState_020bc800->blendDuration) {
            ResetCameraUp_020bca50(g_activeState_020bc800->blendTo);
            g_activeState_020bc800->blendFrom = g_activeState_020bc800->blendTo;
            g_activeState_020bc800->blendTime = -1;
        } else {
            t = EaseProgress_0204a174(g_activeState_020bc800->blendTime, g_activeState_020bc800->blendDuration, g_activeState_020bc800->blendCurve);
            ResetCameraUp_020bca50(FxMul(g_activeState_020bc800->blendFrom, 0x1000 - t) + FxMul(g_activeState_020bc800->blendTo, t));
        }
    }
    if (g_activeState_020bc800->nearestEvent != 0xffff && StageRecord_IsDefeated_02087cc4(g_activeState_020bc800->nearestEvent)) {
        g_activeState_020bc800->nearestEvent = 0xffff;
    }
    for (id = func_ov001_02087928(); id != 0; id = func_ov001_02087944(id)) {
        GetStageEventTargetInfo_02087960(id, &info);
        if (info.id == 9 || info.id == 0x2e || info.id == 0x2f) {
            g_activeState_020bc800->nearestEvent = id;
            break;
        }
    }
    if (g_activeState_020bc800->nearestEvent == 0xffff) {
        FindNearestStageEvent_020bab74();
    }
    if (g_activeState_020bc800->nearestEvent == 0xffff) {
        HideFieldMessageLine_0207166c();
    } else {
        GetStageEventTargetInfo_02087960(g_activeState_020bc800->nearestEvent, &target);
        ShowFieldMessageLine_0207163c(target.displayWidth, (u16)target.displayHeight, target.id, TRUE);
    }
    if (g_activeState_020bc800->nextRecordIndex == -1 && g_activeState_020bc800->recordIndex != -1) {
        switch (g_activeState_020bc800->records[g_activeState_020bc800->recordIndex].kind) {
        case 0:
            break;
        case 1:
            if (g_activeState_020bc800->distance > record->triggerDistance) {
                AdvanceRecordStep_020bc554();
            }
            break;
        case 2:
            advance = TRUE;
            if (QueryStageEventState_0209c758(1, -1)) {
                count = g_activeState_020bc800->activeGroupCount;
                for (i = 1; i < count; i++) {
                    OverlayState *state = g_activeState_020bc800;
                    group = &state->groups[i];
                    if (group->position.z + state->maxDepth[group->slot - 2] < -func_ov031_020bc700()) {
                        world = func_02036230();
                        g_activeState_020bc800->groups[i].hidden = 1;
                        for (j = 0; j < g_activeState_020bc800->groups[i].objectCount; j++) {
                            QuadTree_RemoveObject_02033c60(*world->trees, &g_activeState_020bc800->groups[i].objects[j]);
                        }
                    }
                }
                for (actor = func_ov001_0208723c(); actor != NULL; actor = actor->next) {
                    if (actor->info->category == 6 && !(actor->flags & 8)
                        && ((actor->depth < -func_ov031_020bc700() + 0x5000 && !TestFlagBit9_020a37e4(actor))
                            || (actor->depth < -func_ov031_020bc700() + 0x5000 && actor->depth >= -func_ov031_020bc700()))) {
                        advance = FALSE;
                        break;
                    }
                }
                if (advance) {
                    AdvanceRecordStep_020bc554();
                }
            }
            break;
        }
    }
    if (g_activeState_020bc800->nextRecordIndex != -1 && CanLeaveActiveRecord_020bb010()) {
        if (g_activeState_020bc800->recordIndex != -1) {
            func_ov031_020bb5d8();
        }
        BeginNextRecord_020bb62c();
    }
    if (g_activeState_020bc800->fadeMode == 1) {
        func_ov001_0207b49c(0, 0x1000, 0x1000);
        return;
    }
    {
        s32 limit = (g_activeState_020bc800->brightnessTarget << 12) < 0 ? 0 : (g_activeState_020bc800->brightnessTarget << 12);

        if (g_activeState_020bc800->brightness < limit) {
            g_activeState_020bc800->brightness += 0xcd;
            if (g_activeState_020bc800->brightness > limit) {
                g_activeState_020bc800->brightness = limit;
            }
            func_ov001_0207b49c(0, g_activeState_020bc800->brightnessBase << 12, g_activeState_020bc800->brightness);
        }
    }
}








