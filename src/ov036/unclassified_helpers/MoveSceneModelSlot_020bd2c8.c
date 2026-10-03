#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelViewer {
    VecFx32 moveFrom;
    VecFx32 moveTo;
    s32 moveMode;
    s32 moveDuration;
    s32 moveTimer;
    u8 pad_024[0x74];
    s32 model;
    u8 pad_09C[0x2c];
    VecFx32 position;
    u8 pad_0D4[0x64];
} ModelViewer;

typedef struct SceneWork {
    u8 pad_0000[0x1094];
    ModelViewer *viewers;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3920;
extern int func_ov036_020bc138(int actorId);
extern void func_ov036_020bafe4(ModelViewer *viewer, int x, int y, VecFx32 *out);

void MoveSceneModelSlot_020bd2c8(int actorId, int startX, int startY, int endX, int endY, s32 duration)
{
    SceneWork *work = data_ov036_020c3920.work;
    ModelViewer *viewer = &work->viewers[func_ov036_020bc138(actorId)];

    if (viewer->model == 0) {
        return;
    }
    func_ov036_020bafe4(viewer, startX, startY, &viewer->moveFrom);
    viewer->position = viewer->moveFrom;
    if (duration == 0) {
        return;
    }
    if (startX == endX && startY == endY) {
        return;
    }
    func_ov036_020bafe4(viewer, endX, endY, &viewer->moveTo);
    viewer->moveDuration = duration;
    viewer->moveTimer = duration;
    viewer->moveMode = 3;
}
