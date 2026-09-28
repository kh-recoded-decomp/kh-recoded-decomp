/* Scales the 3x3 portion of a 4x3 matrix and copies its translation row unchanged.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/mtx/calls/MTX_ScaleApply43.c.
 * Original routine: MTX_ScaleApply43. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Scales the 3x3 part through MTX_ScaleApply33 and copies the translation row across. */
extern void MTX_ScaleApply33(const int *src, int *dst, int sx, int sy, int sz);

void MTX_ScaleApply43_01ff94dc(const int *src, int *dst, int sx, int sy, int sz) {
    MTX_ScaleApply33(src, dst, sx, sy, sz);
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
}
