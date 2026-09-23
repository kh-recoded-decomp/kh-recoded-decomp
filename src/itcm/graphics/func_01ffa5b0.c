/* Runs matrix-processing helper calls on selected blocks according to three flag bits.
 * Evidence: Bit tests and helper call block indices/counts in source.
 * Uncertainty: Underlying block formats are opaque.
 * Source: src/calls/func_01ffa13c.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void func_01ffa37c();
void func_01ffa5b0(unsigned int *blocks)
{
    unsigned int flags = *blocks;
    if ((flags & 4) == 0) {
        if ((flags & 2) == 0)
            func_01ffa37c(0x19, blocks + 10, 0xc);
        else
            func_01ffa37c(0x1c, blocks + 0x13, 3);
    } else if ((flags & 2) == 0) {
        func_01ffa37c(0x1a, blocks + 10, 9);
    }
    if ((*blocks & 1) != 0)
        return;
    func_01ffa37c(0x1b, blocks + 1, 3);
}
