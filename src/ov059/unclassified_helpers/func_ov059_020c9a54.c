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

extern const VecFx32 data_02053438;

extern BOOL func_ov021_020a8d1c(s32 group, s32 index);
extern void func_ov021_020a8ab4(TrackState *state);
extern void func_ov021_020a8ca0(TrackState *state, s32 group);
extern void func_ov059_020c7a70(Actor *actor);
extern void *func_ov021_020a8eec(s32 group, s32 index);
extern int Anim_GetFrame_0202f4a0(void *anim, int channel);
extern int func_0202f4b8(void *anim, int channel);
extern FieldSystem *func_02036230(void);
extern void QuadTree_RemoveObject_02033c60(int *root, void *node);
extern void InvokeHandlerOnIndexedRecord_020a8e88(s32 group, s32 index, u32 value);
extern u32 func_ov021_020a8f1c(s32 group, s32 index);
extern void func_ov021_020a8f4c(s32 group, s32 index, u32 flags);
extern void StopSeqArcOrDefault_0204d960(int seqArcNo, int player, int fadeFrames);

void func_ov059_020c9a54(Actor *actor, BOOL start)
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

        if (func_ov021_020a8d1c(actor->effectGroup, 0)) {
            return;
        }
        actor->effectActive = 1;
        func_ov021_020a8ab4(&state);
        state.id = 0;
        state.position = data_02053438;
        state.flag25 = 1;
        state.flag24 = 0;
        state.prevIndex = 0xcd;
        state.index = 0;
        func_ov021_020a8ca0(&state, actor->effectGroup);
        actor->effectTimer = 0;
        func_ov059_020c7a70(actor);
    } else {
        void *anim = func_ov021_020a8eec(actor->effectGroup, 0);
        int frame = Anim_GetFrame_0202f4a0(anim, 0);

        if (frame >= func_0202f4b8(anim, 0) - 0x1000) {
            FieldSystem *system = func_02036230();

            actor->effectActive = 0;
            QuadTree_RemoveObject_02033c60(system->tree->root, actor->quadNode);
            InvokeHandlerOnIndexedRecord_020a8e88(actor->effectGroup, 0, 2);
            func_ov021_020a8f4c(actor->effectGroup, 0, 0);
            StopSeqArcOrDefault_0204d960(0xcd, 0, 5);
        } else {
            func_ov021_020a8f4c(actor->effectGroup, 0, func_ov021_020a8f1c(actor->effectGroup, 0) & ~4);
        }
    }
}
