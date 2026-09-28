/* Invalidates instruction and data caches for the overlay image and clears the uninitialized region following its loaded bytes.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fs/calls/FS_ClearOverlayImage.c.
 * Original routine: FS_ClearOverlayImage. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Invalidates the overlay's code range in both caches and zeroes its BSS. */
extern void IC_InvalidateRange(void *start, void *end);
extern void DC_InvalidateRange(void *start, void *end);
extern void MI_CpuFill8(void *p, int v, unsigned int len);

void FS_InitializeOverlayMemory_0200b7e8(int *ov) {
    int size = ov[3];
    void *base = (void *)ov[1];
    int used = ov[2];
    void *end = (void *)(used + size);
    IC_InvalidateRange(base, end);
    DC_InvalidateRange(base, end);
    MI_CpuFill8((char *)base + used, 0, (unsigned int)end - used);
}
