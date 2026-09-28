extern void MI_Copy36B(const void *src, void *dst);

int G3X_GetVectorMtx_02006bc0(void *dst) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    if (*gxstat & 0x8000000) {
        return -1;
    }
    MI_Copy36B((const void *)(gxstat + 0x20), dst);
    return 0;
}
