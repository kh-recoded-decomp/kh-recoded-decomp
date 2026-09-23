/* Behavior: Maps two packed two-bit end codes to a shape flag.
 * Inputs/outputs and evidence: Switches on masked bits 31..30 and 15..14 and returns one of four constants.
 * Uncertainty: The wider caller meaning of the returned shape flags is unknown.
 * Source: khdays-decomp/src/auto/func_02031644.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int classifyPackedShapeFlags_0204e0a4(int *packedEndCodes) {
    switch (*packedEndCodes & (int)0xc000c000) {
    case 0x00000000:
    case 0x00004000:
    case 0x40004000:
        return 8;
    case 0x00008000:
    case 0x40000000:
    case (int)0x80004000:
        return 0x10;
    case 0x40008000:
    case (int)0x80000000:
    case (int)0x80008000:
    case (int)0xc0004000:
        return 0x20;
    case (int)0xc0000000:
    case (int)0xc0008000:
        return 0x40;
    }
    return 0;
}
