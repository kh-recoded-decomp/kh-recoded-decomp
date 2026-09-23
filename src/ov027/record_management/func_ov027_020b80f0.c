/* Behavior: Allocates a record, initializes its key and owner, registers it, and marks it active.
 * Inputs/outputs and evidence: Gets a record, zeroes 16 bytes, stores two values, registers its embedded field, sets the active word, and returns its address.
 * Uncertainty: Record field roles are suggested by use but allocation/registration subsystem is not established.
 * Source: khdays-decomp/src/overlays/ov000/calls/func_ov000_0205677c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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
