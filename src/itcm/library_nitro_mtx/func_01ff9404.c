/* Transforms a 3D fixed-point vector by a 3x3 matrix without translation.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/mtx/auto/MTX_MultVec33.c.
 * Original routine: MTX_MultVec33. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef signed long fx32;
typedef signed long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst)
{
    register fx32 x, y, z;

    x = vec->x;
    y = vec->y;
    z = vec->z;

    dst->x = (fx32)(((fx64)x * m->_00 + (fx64)y * m->_10 + (fx64)z * m->_20) >> 12);
    dst->y = (fx32)(((fx64)x * m->_01 + (fx64)y * m->_11 + (fx64)z * m->_21) >> 12);
    dst->z = (fx32)(((fx64)x * m->_02 + (fx64)y * m->_12 + (fx64)z * m->_22) >> 12);
}
