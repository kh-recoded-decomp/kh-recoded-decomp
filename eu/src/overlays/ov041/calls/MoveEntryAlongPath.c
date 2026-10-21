#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const s16 gSinFx12Table[];
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern BOOL StepEntryPathModel(StageEntry *entry, fx32 delta, VecFx32 *moved);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Obj_SetPosition(void *object, const VecFx32 *position);

/*
 * Moves an entry along its path model: steps the model delta frames, turns the distance its path node moved
 * (scaled horizontally) by the entry's yaw and then the path's facing, and puts the entry that far from where
 * it stood. TRUE when it has no path running or the path has just ended.
 */
BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta)
{
    VecFx32 position;
    VecFx32 moved;
    VecFx32 offset;
    MtxFx33 pathRotation;
    MtxFx33 yawRotation;
    VecFx32 start;
    BOOL done;

    GetEntryPosition(&start, entry);
    position = start;
    if (entry->pathModel == NULL) {
        return TRUE;
    }
    if (entry->pathModel->state != 2) {
        return TRUE;
    }
    done = StepEntryPathModel(entry, delta, &moved);
    FX_Atan2Idx(entry->pathModel->direction.z, entry->pathModel->direction.x);
    MTX_RotY33_(&yawRotation, gSinFx12Table[entry->slot.node.yaw >> 4],
                gSinFx12Table[(0x400 - (entry->slot.node.yaw >> 4)) & 0xfff]);
    MTX_RotY33_(&pathRotation, gSinFx12Table[entry->pathModel->turn >> 4],
                gSinFx12Table[(0x400 - (entry->pathModel->angle >> 4)) & 0xfff]);
    offset.x = FX_Mul(moved.x, entry->pathModel->scale);
    offset.z = FX_Mul(moved.z, entry->pathModel->scale);
    offset.y = moved.y;
    MTX_MultVec33(&offset, &yawRotation, &offset);
    MTX_MultVec33(&offset, &pathRotation, &offset);
    VEC_Add(&position, &offset, &position);
    Obj_SetPosition(&entry->slot.flags, &position); /* the slot's object starts at its flags */
    return done;
}
