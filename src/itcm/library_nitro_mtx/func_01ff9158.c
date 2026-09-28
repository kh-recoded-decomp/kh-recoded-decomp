/* Applies independent x/y/z fixed-point scales to rows of a 3x3 matrix.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/mtx/auto/MTX_ScaleApply33.c.
 * Original routine: MTX_ScaleApply33. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef signed long fx32;
typedef signed long long fx64;

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

void MTX_ScaleApply33_01ff9158(const MtxFx33 *mtx, MtxFx33 *dst, fx32 x, fx32 y, fx32 z)
{
    dst->m[0] = (fx32)(((fx64)x * mtx->m[0]) >> 12);
    dst->m[1] = (fx32)(((fx64)x * mtx->m[1]) >> 12);
    dst->m[2] = (fx32)(((fx64)x * mtx->m[2]) >> 12);
    dst->m[3] = (fx32)(((fx64)y * mtx->m[3]) >> 12);
    dst->m[4] = (fx32)(((fx64)y * mtx->m[4]) >> 12);
    dst->m[5] = (fx32)(((fx64)y * mtx->m[5]) >> 12);
    dst->m[6] = (fx32)(((fx64)z * mtx->m[6]) >> 12);
    dst->m[7] = (fx32)(((fx64)z * mtx->m[7]) >> 12);
    dst->m[8] = (fx32)(((fx64)z * mtx->m[8]) >> 12);
}
