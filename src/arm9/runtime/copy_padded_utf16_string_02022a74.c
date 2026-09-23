/* Copies up to a fixed number of 16-bit units, then zero-fills remaining units after a copied terminator.
 * Evidence: Loop, terminator check, padding, and return value in source.
 * Uncertainty: This is a bounded UTF-16 style copy; callers define whether units are text.
 * Source: src/auto/func_02020104.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

unsigned short *copy_padded_utf16_string_02022a74(unsigned short *destination, unsigned short *source, int unitCount) {
    unsigned short *writeCursor = destination;
    if (unitCount == 0) return destination;
    do {
        unsigned short *writtenUnit = writeCursor;
        *writeCursor++ = *source++;
        if (*(volatile unsigned short *)writtenUnit == 0) {
            unitCount--;
            if (unitCount != 0) {
                do {
                    *writeCursor++ = 0;
                    unitCount--;
                } while (unitCount != 0);
            }
            return destination;
        }
        unitCount--;
    } while (unitCount != 0);
    return destination;
}
