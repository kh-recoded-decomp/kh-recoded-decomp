#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x2a];
    u8 alpha : 5;
    u8 unk_2A_5 : 3;
    u8 pad_2B[0x39];
    fx32 startAlpha;
    fx32 endAlpha;
    s32 framesLeft;
    u32 totalFrames;
    u8 pad_74[0x14];
    u16 flags;
    u8 pad_8A[0x12];
} ActorSlot;

typedef struct SlotScene {
    u8 pad_0000[0xc80];
    s32 skipAnimation;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3920;
extern int EvaluateInterpolationCurve_02025718(int curve, u32 total, int remaining);
extern int ScaleAroundPivot_020257b0(int t, int to, int from);

void StepActorSlotAlphaFade_020bb71c(ActorSlot *slot)
{
    int remaining = --slot->framesLeft;
    int t;

    if (data_ov036_020c3920.scene->skipAnimation != 0 || remaining == 0) {
        slot->alpha = (u8)(slot->endAlpha >> 12);
        slot->flags &= ~4;
        return;
    }
    t = EvaluateInterpolationCurve_02025718(2, slot->totalFrames, remaining);
    slot->alpha = (u8)(ScaleAroundPivot_020257b0(t, slot->endAlpha, slot->startAlpha) >> 12);
}
