/* Behavior: Compares two byte sequences lexicographically for a specified length.
 * Inputs/outputs and evidence: Returns zero when all bytes match, otherwise -1 or 1 based on the first differing unsigned byte.
 * Uncertainty: This is a bounded byte comparison; it does not look for NUL terminators.
 * Source: khdays-decomp/src/auto/func_0201f844.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int compareByteStrings_02021c54(unsigned char *leftBytes, unsigned char *rightBytes, int length) {
    while (length != 0) {
        if (*leftBytes++ != *rightBytes++) {
            return (leftBytes[-1] < rightBytes[-1]) ? -1 : 1;
        }
        length--;
    }
    return 0;
}
