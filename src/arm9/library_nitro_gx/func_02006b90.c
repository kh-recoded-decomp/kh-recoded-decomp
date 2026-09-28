/* Reads the 3D clip matrix if geometry is idle; returns -1 while busy.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/G3X_GetClipMtx.c.
 * Original routine: G3X_GetClipMtx. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Reads back the clip matrix, but only while the geometry engine is idle; -1 otherwise. */
extern void MI_Copy64B(const void *src, void *dst);

int G3X_GetClipMtx_02006b90(void *dst) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    if (*gxstat & 0x8000000) {
        return -1;
    }
    MI_Copy64B((const void *)(gxstat + 0x10), dst);
    return 0;
}
