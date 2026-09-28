extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int data_020ba3c0;
int CopySourceBlock_020b9f7c(int param_1) {
    int src = data_020ba3c0;
    if (src == 0) return 0;
    MI_CpuCopy8((void *)src, (void *)param_1, 8);
    return param_1;
}
