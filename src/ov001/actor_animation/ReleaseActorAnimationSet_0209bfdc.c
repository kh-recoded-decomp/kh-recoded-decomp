#include "nitro/types.h"

typedef struct AnimationSet {
    u16 count[5];
    u16 texSource;
    void *archiveRecord;
    void **objects[5];
} AnimationSet;

typedef struct ActorModel {
    u8 pad_00[0xc];
    void *activeAnimation;
    u8 pad_10[0x10];
    u8 renderObj[0x54];
} ActorModel;

extern void RemoveAnimationFromRenderObject_02018850(void *renderObj, void *animObj);
extern void func_0202eaf4(AnimationSet *animSet);
extern void func_01ff88c4(void *dst, u32 value, u32 size);

void ReleaseActorAnimationSet_0209bfdc(AnimationSet *animSet, ActorModel *model)
{
    if (animSet->archiveRecord != NULL) {
        RemoveAnimationFromRenderObject_02018850(model->renderObj, model->activeAnimation);
        model->activeAnimation = NULL;
        func_0202eaf4(animSet);
        func_01ff88c4(animSet, 0, sizeof(AnimationSet));
    }
}
