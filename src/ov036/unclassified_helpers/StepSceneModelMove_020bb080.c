#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelViewer {
    VecFx32 moveFrom;
    VecFx32 moveTo;
    s32 moveMode;
    s32 moveRemaining;
    s32 moveDuration;
    u8 pad_024[0xa4];
    VecFx32 position;
    u8 pad_0D4[0x64];
} ModelViewer;

typedef struct SceneWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3920;
extern int EvaluateInterpolationCurve_02025718(int mode, unsigned int duration, int remaining);
extern int ScaleAroundPivot_020257b0(int ratio, int target, int origin);

void StepSceneModelMove_020bb080(ModelViewer *viewer)
{
    VecFx32 position = viewer->position;
    int remaining = --viewer->moveRemaining;

    if (data_ov036_020c3920.work->skipAnimations != 0 || remaining == 0) {
        position = viewer->moveTo;
        viewer->moveDuration = 0;
    } else {
        int ratio = EvaluateInterpolationCurve_02025718(viewer->moveMode, viewer->moveDuration, remaining);

        position.x = ScaleAroundPivot_020257b0(ratio, viewer->moveTo.x, viewer->moveFrom.x);
        position.y = ScaleAroundPivot_020257b0(ratio, viewer->moveTo.y, viewer->moveFrom.y);
    }
    viewer->position = position;
}
