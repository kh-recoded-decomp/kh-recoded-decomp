#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Basis {
    VecFx32 row[3];
} Basis;

typedef struct CameraMatrix {
    Basis basis;
    VecFx32 position;
} CameraMatrix;

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 roll;
} CameraView;

typedef struct CameraShot {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 roll;
    VecFx32 normal;
    s32 usesFocus;
    fx32 positionBlend;
    fx32 rotationBlend;
    s32 normalized : 1;
    s32 dirty : 1;
    s32 arc : 1;
} CameraShot;

typedef struct CameraSequenceEntry {
    CameraShot shot;
    s32 mode;
    s32 duration;
} CameraSequenceEntry;

typedef struct CameraSequence {
    CameraSequenceEntry *entries;
    u16 count;
    u16 index;
    u8 pad08[0x44];
    s32 curveType;
    fx32 blendDuration;
} CameraSequence;

typedef struct EventCameraWork {
    CameraShot current;
    CameraShot start;
    CameraShot end;
    CameraShot source;
    s32 mode;
    s32 timer;
    s32 duration;
    s32 arcAngle;
    s32 eventMode;
    void (*shotCallback)(void *shot);
    CameraMatrix matrix;
    CameraMatrix savedMatrix;
    s32 restoreMatrix;
    CameraSequence *sequence;
    VecFx32 lookDir;
} EventCameraWork;

extern void PlayEventCameraKeys_020c3a34(EventCameraWork *work, void *arg);
extern void BlendEventCameraMatrix_020c3690(EventCameraWork *work);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void TransformVectorByBasis_0204bee8(const VecFx32 *vec, const Basis *basis, VecFx32 *out);
extern void Camera_BuildViewFromState_020c2dd0(EventCameraWork *work, CameraShot *source, CameraView *out);
extern void func_ov046_020c2e60(EventCameraWork *work, void *state);
extern void func_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern void UpdateEventCameraShot_020c3c0c(EventCameraWork *work, void *arg);
extern void UpdateEventCameraCollision_020c3ea8(EventCameraWork *work);
extern void UpdateEventCameraDistance_020c3b60(EventCameraWork *work, void *arg);
extern void UpdateEventCameraOrbitParticle_020c4104(EventCameraWork *work, void *arg);
extern void SetupEventCameraShot_020c4510(EventCameraWork *work, const CameraShot *start, const CameraShot *end, s32 mode, s32 duration);
extern void Camera_BlendToFollowView_020c1304(s32 curveType, fx32 duration);

BOOL UpdateEventCamera_020c377c(EventCameraWork *work, void *arg)
{
    CameraShot startShot;
    CameraView view;
    VecFx32 scaled;
    VecFx32 lookTmp;
    VecFx32 lookDelta;
    VecFx32 lookArg;
    CameraSequence *sequence;
    fx32 projection;

    if (work->sequence != NULL && (work->timer < work->duration || !work->current.arc)) {
        PlayEventCameraKeys_020c3a34(work, arg);
    }
    if (work->end.usesFocus == 1) {
        BlendEventCameraMatrix_020c3690(work);
    }
    if (work->shotCallback != NULL) {
        if (work->end.normalized) {
            work->shotCallback(&work->end);
            if (work->end.usesFocus != 0) {
                VEC_Subtract_01ff9e3c(&work->end.position, &work->matrix.position, &work->end.position);
                TransformVectorByBasis_0204bee8(&work->end.position, &work->matrix.basis, &work->end.position);
                TransformVectorByBasis_0204bee8(&work->end.direction, &work->matrix.basis, &work->end.direction);
                TransformVectorByBasis_0204bee8(&work->end.up, &work->matrix.basis, &work->end.up);
            }
        } else {
            Camera_BuildViewFromState_020c2dd0(work, &work->end, &view);
            work->shotCallback(&view);
            if (work->end.usesFocus != 0) {
                VEC_Subtract_01ff9e3c(&view.position, &work->matrix.position, &view.position);
                TransformVectorByBasis_0204bee8(&view.position, &work->matrix.basis, &view.position);
                TransformVectorByBasis_0204bee8(&view.direction, &work->matrix.basis, &view.direction);
                TransformVectorByBasis_0204bee8(&view.up, &work->matrix.basis, &view.up);
            }
            work->end.position = view.position;
            work->end.up = view.up;
            work->end.roll = view.roll;
            VEC_Subtract_01ff9e3c(&work->end.direction, &work->end.position, &work->end.direction);
            projection = VEC_DotProduct_01ff9e6c(&work->end.direction, &view.direction);
            scaled = view.direction;
            ScaleVecFx32InPlace_0204a5e4(&scaled, projection);
            work->end.direction = scaled;
            VEC_Add_01ff9e0c(&work->end.direction, &work->end.position, &work->end.direction);
        }
    }
    if (work->timer >= work->duration) {
        work->current = work->end;
        if (work->end.usesFocus != 0) {
            func_ov046_020c2e60(work, work);
        }
        if (work->current.normalized) {
            work->lookDir = work->current.direction;
        } else {
            VEC_Subtract_01ff9e3c(&work->current.direction, &work->current.position, &lookDelta);
            lookArg = lookDelta;
            func_01ff9f88(&lookArg, &lookTmp);
            work->lookDir = lookTmp;
        }
        UpdateEventCameraCollision_020c3ea8(work);
        UpdateEventCameraDistance_020c3b60(work, arg);
        UpdateEventCameraOrbitParticle_020c4104(work, arg);
        if (!work->current.arc) {
            if (work->sequence != NULL) {
                work->sequence->index++;
                sequence = work->sequence;
                if (sequence->index <= sequence->count) {
                    if (sequence->index != sequence->count) {
                        startShot = work->source;
                        SetupEventCameraShot_020c4510(work, &startShot, &work->sequence->entries[work->sequence->index].shot,
                                                      work->sequence->entries[work->sequence->index].mode,
                                                      work->sequence->entries[work->sequence->index].duration);
                        if (work->restoreMatrix != 0) {
                            work->restoreMatrix = 0;
                            work->matrix = work->savedMatrix;
                        }
                    } else {
                        Camera_BlendToFollowView_020c1304(sequence->curveType, sequence->blendDuration);
                        if (sequence->blendDuration != 0) {
                            work->sequence = sequence;
                        }
                    }
                    goto advance;
                }
            }
            return TRUE;
        }
    } else {
        UpdateEventCameraShot_020c3c0c(work, arg);
        UpdateEventCameraDistance_020c3b60(work, arg);
        UpdateEventCameraOrbitParticle_020c4104(work, arg);
    }
advance:
    work->timer += 0x1000;
    return FALSE;
}
