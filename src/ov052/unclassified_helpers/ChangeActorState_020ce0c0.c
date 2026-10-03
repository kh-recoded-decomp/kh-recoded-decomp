#include "nitro/types.h"

typedef void (*ActorCallback)(int entity, int value);

extern int GetTransitionReaction_020ce01c(int entity, int next, int current, int extra);
extern void SelectAnimationById_020ac8f4(int selector, int id);
extern int func_0202f4b8(int state, int arg);
extern void SetBlendTableAndBlendTrack_020cbf58(int entity, int blendTable, int trackIndex, int blendIndex, int frameCount);
extern void func_ov052_020cfb88(int entity, int index, int state, int frames);

void ChangeActorState_020ce0c0(int entity, int blendTable, int state, int blendIndex, int frames)
{
    int i;
    int current = *(int *)(entity + 0x75c);
    int count = frames;
    if (count < 0) {
        count = GetTransitionReaction_020ce01c(entity, state, current, *(int *)(entity + 0x9b8));
    }
    SelectAnimationById_020ac8f4(entity + 0x874, state);
    if (count > 0 && *(int *)(entity + 0x768) != 0) {
        int time = func_0202f4b8(*(int *)(entity + 0x230) + 4, 0) - 0x1000;
        ActorCallback callback = *(ActorCallback *)(entity + 0x1fc);
        if (callback != NULL) {
            callback(entity, time);
        }
    }
    SetBlendTableAndBlendTrack_020cbf58(entity, blendTable, 0, blendIndex, count);
    for (i = 0; i < 2; i++) {
        func_ov052_020cfb88(entity, i, state, count);
    }
    if (*(ActorCallback *)(entity + 0x1fc) != NULL) {
        (*(ActorCallback *)(entity + 0x1fc))(entity, 0);
    }
    *(int *)(entity + 0x75c) = state;
    *(int *)(entity + 0x768) = 0;
}
