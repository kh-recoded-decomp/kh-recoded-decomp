/* Conditionally invokes a helper on an embedded block based on resource state and an object flag.
 * Evidence: Global state checks and computed pointer offsets in source.
 * Uncertainty: Specific resource and operation are not established.
 * Source: src/calls/func_0201ef58.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void func_02002aa8(void *p);
extern struct { char _0[4]; char *field_4; char _8[0x34]; int field_3c; } data_02060564;

int func_0202c438(void)
{
    if (data_02060564.field_3c <= 0) {
        if (*(int *)(data_02060564.field_4 + 0x448) == 0) goto out;
    }
    func_02002aa8(data_02060564.field_4 + 0x4c + 0x400);
out:
    return 1;
}
