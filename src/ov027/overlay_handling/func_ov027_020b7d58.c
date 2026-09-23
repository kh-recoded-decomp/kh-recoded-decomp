/* Initializes a container from configuration and allocates three zeroed arrays; array purposes are unknown. Evidence: Source implementation directly performs the described operations; see src/overlays/ov002/calls/func_ov002_020543b8.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/overlays/ov002/calls/func_ov002_020543b8.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MI_CpuFill8(void *destination, int fill_value, int byte_count);
extern void NNS_FndInitList(int list, int offset);
extern int NNSi_FndAllocFromDefaultExpHeap(int byte_count);
void func_ov027_020b7d58(int container, int configuration) {
    MI_CpuFill8((void *)container, 0, 0x4c);
    NNS_FndInitList(container, 0x2c);
    *(int *)(container + 0x30) = *(int *)configuration;
    *(int *)(container + 0x34) = *(int *)(configuration + 4);
    *(int *)(container + 0x38) = *(int *)(configuration + 8);
    *(int *)(container + 0x3c) = *(int *)(configuration + 0xc);
    *(int *)(container + 0x40) = *(int *)(configuration + 0x10);
    *(int *)(container + 0xc) = NNSi_FndAllocFromDefaultExpHeap(*(int *)configuration * 0x38);
    *(int *)(container + 0x10) = NNSi_FndAllocFromDefaultExpHeap(*(int *)(configuration + 4) * 0x30);
    *(int *)(container + 0x14) = NNSi_FndAllocFromDefaultExpHeap(*(int *)(configuration + 8) << 4);
    MI_CpuFill8((void *)*(int *)(container + 0xc), 0, *(int *)configuration * 0x38);
    MI_CpuFill8((void *)*(int *)(container + 0x10), 0, *(int *)(configuration + 4) * 0x30);
    MI_CpuFill8((void *)*(int *)(container + 0x14), 0, *(int *)(configuration + 8) << 4);
}
