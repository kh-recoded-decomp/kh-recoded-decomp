#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Basis {
    VecFx32 row[3];
} Basis;

typedef struct CameraMatrix {
    Basis basis;
    VecFx32 position;
} CameraMatrix;

typedef struct EventCameraWork {
    u8 pad000[0x38];
    fx32 positionBlend;
    fx32 rotationBlend;
    u8 pad040[0xe8];
    CameraMatrix matrix;
} EventCameraWork;

extern void func_ov046_020c2d8c(CameraMatrix *out);
extern void RotateTowardVector_0204b404(const VecFx32 *from, const VecFx32 *to, fx32 ratio, VecFx32 *out);
extern void BuildBasisFromForward_0204bf70(const VecFx32 *forward, const VecFx32 *up, Basis *basis);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void BlendEventCameraMatrix_020c3690(EventCameraWork *work)
{
    CameraMatrix target;
    Basis built;
    Basis rebuilt;
    Basis *basis;
    CameraMatrix *source;
    VecFx32 *focus;

    if (work->positionBlend == FX32_ONE && work->rotationBlend == FX32_ONE) {
        func_ov046_020c2d8c(&work->matrix);
        return;
    }
    source = &target;
    func_ov046_020c2d8c(source);
    if (work->rotationBlend == FX32_ONE) {
        work->matrix.basis = target.basis;
    } else {
        basis = &work->matrix.basis;
        RotateTowardVector_0204b404(&basis->row[2], &source->basis.row[2], work->rotationBlend, &basis->row[2]);
        RotateTowardVector_0204b404(&basis->row[1], &source->basis.row[1], work->rotationBlend, &basis->row[1]);
        BuildBasisFromForward_0204bf70(&basis->row[2], &basis->row[1], &built);
        rebuilt = built;
        *(MtxFx33 *)basis = *(MtxFx33 *)&rebuilt;
        NegateVecFx32_0204aa40(&basis->row[0]);
    }
    if (work->positionBlend == FX32_ONE) {
        work->matrix.position = target.position;
        return;
    }
    focus = &target.position;
    VEC_Subtract_01ff9e3c(&work->matrix.position, focus, &work->matrix.position);
    ScaleVecFx32InPlace_0204a5e4(&work->matrix.position, FX32_ONE - work->positionBlend);
    VEC_Add_01ff9e0c(&work->matrix.position, focus, &work->matrix.position);
}
