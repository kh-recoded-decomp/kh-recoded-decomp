/* Starts a resource operation, selects operation 2, and returns whether its status query is zero.
 * Evidence: Three helper calls and returned comparison in source.
 * Uncertainty: Exact resource operation is opaque.
 * Source: src/calls/func_02024d68.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int data_02060534;
extern void func_0200fdd8(int unknownMode0, int unknownMode1, void *stateBlock, int unknownMode2);
extern void func_0201018c(int unknownMode);
extern int func_0201019c(int unknownMode);

int func_0202b5d4(void) {
    func_0200fdd8(0, 4, &data_02060534, 5);
    func_0201018c(2);
    return func_0201019c(2) == 0;
}
