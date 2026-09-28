#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    VecFx32 row[3];
} MtxFx33;

typedef struct QuatFx32 {
    fx32 c[4];
} QuatFx32;

extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern int func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern void func_0202f628(QuatFx32 *dst, MtxFx33 *mtx);
extern void ScaleVector4ByReciprocalMagnitude_0202fc50(QuatFx32 *dst, QuatFx32 *src);
extern void multiplyFixedPointQuaternions_0202f93c(QuatFx32 *dst, QuatFx32 *a, QuatFx32 *b);
extern void QuaternionToRotationMatrix_0202f808(MtxFx33 *mtx, QuatFx32 *quat);
extern void MTX_ScaleApply33_01ff9158(MtxFx33 *dst, MtxFx33 *src, fx32 sx, fx32 sy, fx32 sz);
extern QuatFx32 g_correctionQuat_02055824;

void ApplyQuaternionCorrectionToMatrix_0202f090(MtxFx33 *mtx, s32 unused2, s32 unused3, s32 unused4) {
    fx32 scaleX, scaleY, scaleZ;
    QuatFx32 quat;

    scaleX = VEC_Mag_01ff9f28(&mtx->row[0]);
    scaleY = VEC_Mag_01ff9f28(&mtx->row[1]);
    scaleZ = VEC_Mag_01ff9f28(&mtx->row[2]);
    func_01ffaff4(&mtx->row[0], &mtx->row[0]);
    func_01ffaff4(&mtx->row[1], &mtx->row[1]);
    func_01ffaff4(&mtx->row[2], &mtx->row[2]);
    func_0202f628(&quat, mtx);
    ScaleVector4ByReciprocalMagnitude_0202fc50(&quat, &quat);
    multiplyFixedPointQuaternions_0202f93c(&quat, &quat, &g_correctionQuat_02055824);
    QuaternionToRotationMatrix_0202f808(mtx, &quat);
    MTX_ScaleApply33_01ff9158(mtx, mtx, scaleX, scaleY, scaleZ);
}
