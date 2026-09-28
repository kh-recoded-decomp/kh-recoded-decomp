extern int func_020b7980(int recordPool);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void func_02014dd0(int ownerId, int registrationAddress);
int func_ov027_020b80f0(int recordPool, int ownerId, unsigned short recordId) {
    int record = func_020b7980(recordPool);
    MI_CpuFill8((void *)record, 0, 0x10);
    *(unsigned short *)(record) = recordId;
    *(int *)(record + 4) = ownerId;
    func_02014dd0(ownerId, record + 8);
    *(int *)(record + 0xc) = 1;
    return record;
}
