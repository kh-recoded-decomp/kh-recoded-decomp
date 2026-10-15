#pragma opt_common_subs off

#include "nitro/types.h"

typedef struct ActionMarkerActor ActionMarkerActor;

typedef struct ActionRecord {
    u8 reserved00[0x3c];
    u32 flags;
    u8 reserved40[0x50];
} ActionRecord;

typedef struct ActionMarkerState {
    u32 kind;
    u32 type;
    u32 reserved08;
    void *info;
    u8 reserved10[0x58 - 0x10];
    s32 index;
    s32 startFrame;
    s32 endFrame;
    s32 style;
    u32 reserved68;
    ActionRecord *records;
    u32 reserved70;
    BOOL emitHitMarkers;
    u32 reserved78;
    s16 *groupId;
    u8 reserved80;
    s8 markerHandle;
} ActionMarkerState;

typedef struct ActionHitEntry {
    void (*onHit)(ActionMarkerActor *, void *, void *);
    void *context;
    u8 reserved08[0x18];
} ActionHitEntry;

struct ActionMarkerActor {
    u8 reserved00[0x1f8];
    void (*onEnd)(ActionMarkerActor *, int, int);
    u8 reserved1fc[0x234 - 0x1fc];
    u32 modelFlags;
    u8 reserved238[0x760 - 0x238];
    s32 frame;
    u32 reserved764;
    BOOL modeChangePending;
    u8 reserved76c[0x9b4 - 0x76c];
    u8 player;
    u8 reserved9b5[0x9ec - 0x9b5];
    s32 markerTarget;
    u8 reserved9f0[0xa51 - 0x9f0];
    s8 actionIndex;
    u8 reserveda52[0x1078 - 0xa52];
    ActionMarkerState *action;
    u8 reserved107c[0x10ec - 0x107c];
    void (*onEvent)(ActionMarkerActor *, int);
};

typedef char ActionRecordSizeCheck[sizeof(ActionRecord) == 0x90 ? 1 : -1];
typedef char ActionHitEntrySizeCheck[sizeof(ActionHitEntry) == 0x20 ? 1 : -1];
typedef char ActionMarkerGroupOffsetCheck[
    (u32)&((ActionMarkerState *)0)->groupId == 0x7c ? 1 : -1];
typedef char ActionMarkerHandleOffsetCheck[
    (u32)&((ActionMarkerState *)0)->markerHandle == 0x81 ? 1 : -1];
typedef char ActionMarkerStateOffsetCheck[
    (u32)&((ActionMarkerActor *)0)->action == 0x1078 ? 1 : -1];

extern BOOL func_ov001_02072040(void);
extern void func_ov052_020cfdd4(ActionMarkerActor *, ActionRecord *, int);
extern void ApplyAnimRootMotion(ActionMarkerActor *, ActionRecord *);
extern void InitSlotEntryFromRecord(ActionHitEntry *, void *, int, void *, int);
extern void SpawnGroupHitMarker(ActionMarkerActor *, void *, void *);
extern void SetGroupSlotTarget(int groupId, int index, s32 target);
extern BOOL IsGroupMemberActive(int groupId, int index);
extern void StopAndClearSoundEmitter(int groupId, int index);
extern void SpawnTimedAuraMarker(ActionMarkerState *, ActionMarkerActor *, s32 frame);
extern int ProcessTargetHitEntries(ActionMarkerActor *, ActionRecord *, ActionHitEntry *);
extern BOOL UpdateActionPhase(ActionMarkerActor *, ActionRecord *, int);
extern BOOL HandlePendingCommand(ActionMarkerActor *);

void UpdateActionHitMarkers(ActionMarkerActor *actor)
{
    BOOL which = func_ov001_02072040();
    ActionMarkerState *state = actor->action;
    ActionRecord *record = &state->records[actor->actionIndex];
    ActionHitEntry hitEntry;
    s16 groupId;

    func_ov052_020cfdd4(actor, record, which);
    ApplyAnimRootMotion(actor, record);
    InitSlotEntryFromRecord(&hitEntry, record, which, state, actor->player);
    if (state->emitHitMarkers != FALSE) {
        hitEntry.onHit = SpawnGroupHitMarker;
        hitEntry.context = state;
    }
    if (state->groupId != NULL) {
        groupId = *state->groupId;
        if (state->markerHandle != -1) {
            SetGroupSlotTarget(groupId, state->markerHandle, actor->markerTarget);
            if (actor->frame >= state->endFrame
                && IsGroupMemberActive(groupId, state->markerHandle)) {
                StopAndClearSoundEmitter(groupId, state->markerHandle);
                state->markerHandle = -1;
            }
        }
        SpawnTimedAuraMarker(state, actor, actor->frame);
    }
    if (!ProcessTargetHitEntries(actor, record, &hitEntry)
        && !UpdateActionPhase(actor, record, which) && actor->modeChangePending) {
        u32 modelFlag4 = actor->modelFlags & 4;

        if (!HandlePendingCommand(actor)) {
            if (modelFlag4) {
                if (!(record->flags & 4)) {
                    actor->onEvent(actor, 1);
                    if (actor->onEnd != NULL) {
                        actor->onEnd(actor, 0, -1);
                    }
                } else {
                    actor->onEvent(actor, 5);
                }
            } else {
                actor->onEvent(actor, 4);
            }
        }
    }
}
