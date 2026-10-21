#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern int func_0202f4cc(void *model, int track);
extern void func_01ffb2f8(void *model, u16 track, int frame);
extern void SceneNode_Draw(void *node);
extern void GetPathNodeOffset(StagePathModel *model, VecFx32 *position, VecFx32 *delta);

/*
 * Plays an entry's path model delta frames further (stopping on its last frame), updates where its path node is
 * and how far it moved; TRUE once the last frame is reached.
 */
BOOL StepEntryPathModel(StageEntry *entry, fx32 delta, VecFx32 *moved)
{
    StagePathModel *model = entry->pathModel;
    fx32 frame = model->frame + delta;
    fx32 last = func_0202f4cc(model, 0) - FX32_ONE;

    if (frame > last) {
        frame = last;
    }
    func_01ffb2f8(model, 0, frame);
    model->renderFlags |= 3;
    SceneNode_Draw(model);
    model->renderFlags &= ~3;
    GetPathNodeOffset(model, &model->position, moved);
    model->frame = frame;
    if (frame == last) {
        model->state = 3;
        return TRUE;
    }
    return FALSE;
}
