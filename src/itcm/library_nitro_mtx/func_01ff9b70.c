/* Builds a 4x3 view matrix from camera position, up direction, and target via normalize, cross, and dot operations.
 * The exact public SDK symbol is not established from the body, so the target address-based name is retained; behavior is limited to the implemented operation. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/mtx/calls/func_01ff9c04.c.
 * Original routine: func_01ff9c04. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef signed long fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx)
{
    VecFx32 vLook, vRight, vUp;

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;

    func_01ff9f88(&vLook, &vLook);
    VEC_CrossProduct(camUp, &vLook, &vRight);
    func_01ff9f88(&vRight, &vRight);
    VEC_CrossProduct(&vLook, &vRight, &vUp);

    mtx->_00 = vRight.x;
    mtx->_01 = vUp.x;
    mtx->_02 = vLook.x;
    mtx->_10 = vRight.y;
    mtx->_11 = vUp.y;
    mtx->_12 = vLook.y;
    mtx->_20 = vRight.z;
    mtx->_21 = vUp.z;
    mtx->_22 = vLook.z;
    mtx->_30 = -VEC_DotProduct(camPos, &vRight);
    mtx->_31 = -VEC_DotProduct(camPos, &vUp);
    mtx->_32 = -VEC_DotProduct(camPos, &vLook);
}
