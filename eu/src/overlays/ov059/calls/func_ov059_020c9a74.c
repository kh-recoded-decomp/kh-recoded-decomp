#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flag24;
    u8 flag25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct QuadTreeRef {
    int *root;
} QuadTreeRef;

typedef struct FieldSystem {
    u8 pad_00[4];
    QuadTreeRef *tree;
} FieldSystem;

typedef struct Actor {
    u8 pad_0000[0x171c];
    s32 flagsLow : 14;
    s32 effectActive : 1;
    s32 flagsHigh : 17;
    s32 effectTimer;
    u8 pad_1724[0x1774 - 0x1724];
    u8 quadNode[0x1816 - 0x1774];
    s16 effectGroup;
} Actor;

extern const VecFx32 data_0205344c;

extern BOOL IsGroupMemberActive(s32 group, s32 index);
extern void ResetAnimationTrackState(TrackState *state);
extern void func_ov021_020a8cc0(TrackState *state, s32 group);
extern void Actor_TrySpawnIdleEffect(Actor *actor);
extern void *GetGroupMemberData(s32 group, s32 index);
extern int Anim_GetFrame(void *anim, int channel);
extern int func_0202f4cc(void *anim, int channel);
extern FieldSystem *GetActorRegistry(void);
extern void QuadTree_RemoveObject(int *root, void *node);
extern void InvokeHandlerOnIndexedRecord(s32 group, s32 index, u32 value);
extern u32 GetGroupSlotValue(s32 group, s32 index);
extern void SetSlotEntryValue(s32 group, s32 index, u32 flags);
extern void StopSeqArcOrDefault(int seqArcNo, int player, int fadeFrames);

void func_ov059_020c9a74(Actor *actor, BOOL start)
{
    BOOL ready;

    if (start) {
        ready = actor->effectActive ? FALSE : TRUE;
    } else {
        ready = actor->effectActive;
    }
    if (!ready) {
        return;
    }
    if (start) {
        TrackState state;

        if (IsGroupMemberActive(actor->effectGroup, 0)) {
            return;
        }
        actor->effectActive = 1;
        ResetAnimationTrackState(&state);
        state.id = 0;
        state.position = data_0205344c;
        state.flag25 = 1;
        state.flag24 = 0;
        state.prevIndex = 0xcd;
        state.index = 0;
        func_ov021_020a8cc0(&state, actor->effectGroup);
        actor->effectTimer = 0;
        Actor_TrySpawnIdleEffect(actor);
    } else {
        void *anim = GetGroupMemberData(actor->effectGroup, 0);
        int frame = Anim_GetFrame(anim, 0);

        if (frame >= func_0202f4cc(anim, 0) - 0x1000) {
            FieldSystem *system = GetActorRegistry();

            actor->effectActive = 0;
            QuadTree_RemoveObject(system->tree->root, actor->quadNode);
            InvokeHandlerOnIndexedRecord(actor->effectGroup, 0, 2);
            SetSlotEntryValue(actor->effectGroup, 0, 0);
            StopSeqArcOrDefault(0xcd, 0, 5);
        } else {
            SetSlotEntryValue(actor->effectGroup, 0, GetGroupSlotValue(actor->effectGroup, 0) & ~4);
        }
    }
}
