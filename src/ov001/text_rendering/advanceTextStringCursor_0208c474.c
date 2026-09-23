/* Behavior: Advances a text cursor past one encoded glyph or control token.
 * Inputs/outputs and evidence: Advances by one, two or three bytes based on the lead byte; control code 3 consumes one extra byte and returns a line-break indicator.
 * Uncertainty: Encoding is a limited UTF-8-like scheme with control tokens, not a full Unicode decoder.
 * Source: khdays-decomp/src/overlays/ov002/auto/func_ov002_020754bc.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int advanceTextStringCursor_0208c474(int textBytes, int *byteCursor) {
    int cursor = *byteCursor;

    while (*(signed char *)(textBytes + cursor) != 0) {
        int leadByte = ((signed char *)textBytes)[cursor];
        if (leadByte >= 1 && leadByte < 0x20) {
            *byteCursor += 1;
            if (leadByte == 3) {
                *byteCursor += 1;
                return 1;
            }
        } else if (leadByte >= 0x20 && leadByte < 0x80) {
            *byteCursor += 1;
        } else {
            if ((leadByte & 0xe0) == 0xc0) {
                *byteCursor += 2;
            } else if ((leadByte & 0xf0) == 0xe0) {
                *byteCursor += 3;
            }
        }
        cursor = *byteCursor;
    }
    return 0;
}
