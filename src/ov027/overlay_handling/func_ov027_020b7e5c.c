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
