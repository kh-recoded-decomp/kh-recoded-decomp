#include "nitro/types.h"
#include "nitro/fx_types.h"

extern BOOL RestoreNodeGeometryMatrix_02019d8c(void *renderObj, VecFx32 *posMtx, void *nrmMtx, u32 nodeId);
extern fx32 VEC_Mag_01ff9f28(VecFx32 *vec);
extern void func_01ffaff4(VecFx32 *dst, VecFx32 *src);
extern void func_0202f628(fx32 *quat, VecFx32 *mtx);
extern fx32 ScaleVector4ByReciprocalMagnitude_0202fc50(fx32 *dst, fx32 *src);
extern void multiplyFixedPointQuaternions_0202f93c(fx32 *dst, fx32 *a, fx32 *b);
extern void QuaternionToRotationMatrix_0202f808(VecFx32 *mtx, fx32 *quat);
extern void MTX_ScaleApply33_01ff9158(VecFx32 *dst, VecFx32 *src, fx32 x, fx32 y, fx32 z);

extern fx32 g_correctionQuaternion_0209e438[4];

/* Restores a node matrix and optionally corrects its rotation. */
BOOL RestoreNodeMatrixWithRotationCorrection_0208f2b4(u8 *node, VecFx32 *posMtx, u32 nodeId, BOOL applyCorrection)
{
    fx32 quat[4];
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;

    if (RestoreNodeGeometryMatrix_02019d8c(node + 0x20, posMtx, 0, nodeId)) {
        if (applyCorrection) {
            scaleX = VEC_Mag_01ff9f28(&posMtx[0]);
            scaleY = VEC_Mag_01ff9f28(&posMtx[1]);
            scaleZ = VEC_Mag_01ff9f28(&posMtx[2]);
            func_01ffaff4(&posMtx[0], &posMtx[0]);
            func_01ffaff4(&posMtx[1], &posMtx[1]);
            func_01ffaff4(&posMtx[2], &posMtx[2]);
            func_0202f628(quat, posMtx);
            ScaleVector4ByReciprocalMagnitude_0202fc50(quat, quat);
            multiplyFixedPointQuaternions_0202f93c(quat, quat, g_correctionQuaternion_0209e438);
            QuaternionToRotationMatrix_0202f808(posMtx, quat);
            MTX_ScaleApply33_01ff9158(posMtx, posMtx, scaleX, scaleY, scaleZ);
        }
        return TRUE;
    }
    return FALSE;
}
