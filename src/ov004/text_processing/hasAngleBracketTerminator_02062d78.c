/* Behavior: Checks whether a zero-terminated 16-bit string starts with '<' or ends with '>'.
 * Inputs/outputs and evidence: Returns true for leading 0x3c, otherwise scans to NUL and checks trailing 0x3e, with a mode-2 override.
 * Uncertainty: The string's format and the override mode meaning are unknown.
 * Source: khdays-decomp/src/overlays/ov011/auto/func_ov011_0205cfa8.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int hasAngleBracketTerminator_02062d78(unsigned short *text, int mode) {
    unsigned short firstCodeUnit;
    if (text == 0) {
        return 0;
    }
    firstCodeUnit = *text;
    if (firstCodeUnit == 0x3c) {
        return 1;
    }
    if (firstCodeUnit != 0) {
        do {
            text++;
        } while (*text != 0);
    }
    return text[-1] == 0x3e || mode == 2;
}
