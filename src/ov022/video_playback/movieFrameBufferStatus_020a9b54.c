/* Reports whether a decoded movie buffer is available and its transfer mode.
 * Evidence: The status word at +0x20 gates the result; the word at +0x28 selects 0x80 or 0x100.
 * Uncertainty: The exact meanings of these two fields and returned modes are unknown.
 * Source: khdays-decomp/src/overlays/ov024/auto/func_ov024_02085878.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int movieFrameBufferStatus_020a9b54(const unsigned char *movieContext)
{
    if (*(const int *)(movieContext + 0x20) == 0) {
        return 0;
    }
    if (*(const int *)(movieContext + 0x28) != 0) {
        return 0x80;
    }
    return 0x100;
}
