/* Applies x/y fixed-point scales to rows of a 2x2 matrix.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/mtx/auto/MTX_ScaleApply22.c.
 * Original routine: MTX_ScaleApply22. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef struct { int _00, _01, _10, _11; } MtxFx22;

void MTX_ScaleApply22_02005954(const MtxFx22 *src, MtxFx22 *dst, int sx, int sy) {
    dst->_00 = (int)(((long long)sx * src->_00) >> 12);
    dst->_01 = (int)(((long long)sx * src->_01) >> 12);
    dst->_10 = (int)(((long long)sy * src->_10) >> 12);
    dst->_11 = (int)(((long long)sy * src->_11) >> 12);
}
