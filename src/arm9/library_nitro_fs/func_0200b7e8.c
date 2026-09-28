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
