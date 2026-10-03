#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s16 animId;
    s16 loopCount;
} AnimSequenceClip;

typedef struct {
    s8 state;
    s8 clipIndex;
    s8 clipCount;
    s8 loopCounter;
    AnimSequenceClip clips[4];
    fx32 frame;
    u8 pad_18[0x04];
    VecFx32 position;
    VecFx32 target;
    VecFx32 startPosition;
} AnimSequence;

typedef struct {
    u8 animState[0x20];
    u32 renderFlags;
    u8 pad_24[0xd8 - 0x24];
    u8 blendTable[4];
} ActorModel;

typedef struct {
    u8 pad_00[0x0c];
    ActorModel model;
} StageObjectRecord;

typedef struct {
    fx32 x, y, z, w;
} Quat;

extern u16 FindStageObjectByOwner_020995c4(u16 slot, u32 owner);
extern StageObjectRecord *GetStageObjectRecord_0209c0a0(u32 id);
extern void selectJointAnimationBlend_0202f2cc(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern int *func_01ffb2f8(void *animationState, int trackIndex, int frame);
extern u16 AdvanceAnimationTracks_0202ef24(void *animationState, fx32 delta);
extern void func_ov001_0208f4f4(ActorModel *model);
extern BOOL RestoreNodeGeometryMatrix_02019d8c(void *renderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeID);
extern void QuaternionFromRotationMatrix_0202f628(Quat *quat, const MtxFx43 *mtx);
extern int ScaleVector4ByReciprocalMagnitude_0202fc50(Quat *vector, Quat *source);
extern void multiplyFixedPointQuaternions_0202f93c(Quat *result, const Quat *left, const Quat *right);
extern void QuaternionToRotationMatrix_0202f808(MtxFx43 *matrix, const Quat *quat);
extern const Quat data_ov010_020a1d5c;

void AnimSequence_GetCurrentPosition_020a1c74(AnimSequence *seq, VecFx32 *out)
{
    MtxFx43 mtx;
    Quat quat;
    ActorModel *model;
    AnimSequenceClip *clip;

    model = &GetStageObjectRecord_0209c0a0(FindStageObjectByOwner_020995c4(0, 2))->model;
    clip = &seq->clips[seq->clipIndex];
    model->renderFlags |= 4;
    selectJointAnimationBlend_0202f2cc(model, 0, model->blendTable, clip->animId);
    func_01ffb2f8(model, 0, seq->frame);
    AdvanceAnimationTracks_0202ef24(model, 0);
    func_ov001_0208f4f4(model);
    if (RestoreNodeGeometryMatrix_02019d8c(&model->renderFlags, &mtx, NULL, 0)) {
        QuaternionFromRotationMatrix_0202f628(&quat, &mtx);
        ScaleVector4ByReciprocalMagnitude_0202fc50(&quat, &quat);
        multiplyFixedPointQuaternions_0202f93c(&quat, &quat, &data_ov010_020a1d5c);
        QuaternionToRotationMatrix_0202f808(&mtx, &quat);
    }
    out->x = seq->position.x + mtx._30;
    out->y = seq->position.y + mtx._31;
    out->z = seq->position.z + mtx._32;
    model->renderFlags &= ~4;
}
