/* Behavior: Invalidates the cache for and reads one halfword from a two-dimensional table.
 * Inputs/outputs and evidence: Computes base + 0x20 + row*0x24 + column*2, invalidates two bytes, then reads a signed halfword.
 * Uncertainty: The table's semantic fields are unknown.
 * Source: khdays-decomp/src/calls/func_02008d1c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void DC_InvalidateRange(void *addr, unsigned size);
extern char *data_02059780;

short readInvalidatedHalfwordEntry_0200f5c4(int rowIndex, int columnIndex) {
    DC_InvalidateRange(data_02059780 + 0x20 + rowIndex * 0x24 + columnIndex * 2, 2);
    return *(short *)(data_02059780 + 0x20 + rowIndex * 0x24 + columnIndex * 2);
}
