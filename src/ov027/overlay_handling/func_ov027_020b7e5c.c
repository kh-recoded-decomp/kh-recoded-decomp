/* Allocates and fills a fixed-size record and marks it active; field purposes are unknown. Evidence: Source implementation directly performs the described operations; see src/overlays/ov000/calls/func_ov000_0205657c.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/overlays/ov000/calls/func_ov000_0205657c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_020b78ec(int owner_id);
extern void MI_CpuFill8(void *destination, int fill_value, int byte_count);
extern int func_020b789c(int owner_id, int related_id);
int func_ov027_020b7e5c(int owner_id, int related_id, unsigned short record_type, unsigned short first_id, unsigned short second_id,
                        short first_value, short second_value, int record_data) {
    int record = func_020b78ec(owner_id);
    MI_CpuFill8((void *)record, 0, 0x38);
    *(unsigned short *)(record) = record_type;
    *(unsigned short *)(record + 6) = first_id;
    *(unsigned short *)(record + 8) = second_id;
    *(int *)(record + 0x10) = record_data;
    *(short *)(record + 0xa) = first_value;
    *(short *)(record + 0xc) = second_value;
    *(int *)(record + 0x18) = func_020b789c(owner_id, related_id);
    *(int *)(record + 0x14) = 1;
    return record;
}
