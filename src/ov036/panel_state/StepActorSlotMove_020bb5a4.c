#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x10];
    fx32 posX;
    fx32 posY;
    u8 pad_18[0x18];
    fx32 moveFrom;
    fx32 moveTo;
    s32 moveCurve;
    s32 moveAxis;
    s32 framesLeft;
    u32 totalFrames;
    u8 pad_48[0x40];
    u16 flags;
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

void StepActorSlotMove_020bb5a4(ActorSlot *slot)
{
    int remaining = --slot->framesLeft;
    int t;

    if (data_ov036_020c3920.scene->skipAnimation != 0 || remaining == 0) {
        if (slot->moveAxis != 0) {
            slot->posY = slot->moveTo;
        } else {
            slot->posX = slot->moveTo;
        }
        slot->flags &= ~1;
        return;
    }
    t = EvaluateInterpolationCurve_02025718(slot->moveCurve, slot->totalFrames, remaining);
    if (slot->moveAxis != 0) {
        slot->posY = ScaleAroundPivot_020257b0(t, slot->moveTo, slot->moveFrom);
    } else {
        slot->posX = ScaleAroundPivot_020257b0(t, slot->moveTo, slot->moveFrom);
    }
}
