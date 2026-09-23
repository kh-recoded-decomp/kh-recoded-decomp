/* Behavior: Lazily fills and returns a cached matrix buffer.
 * Inputs/outputs and evidence: If a global state bit is clear, calls a matrix helper to populate the buffer and sets the bit.
 * Uncertainty: Exact matrix form and transform meaning are inferred from names/size only.
 * Source: khdays-decomp/src/calls/func_02015b2c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void func_020193b8(void *sourceMatrix, void *cachedMatrix);
extern struct { char padding[0xd4]; int flags; } data_0205a924;
extern char data_0205a92c[];
extern char data_0205aabc[];

void *getCachedMatrix43_020195b4(void)
{
    if ((data_0205a924.flags & 0x10) == 0) {
        func_020193b8(data_0205a92c, data_0205aabc);
        data_0205a924.flags |= 0x10;
    }
    return data_0205aabc;
}
