/* Paired with 020baaf8: writes the shared ov039 state word at +0xc9c4.
 * Ghidra shows both functions using the pointer at 020bea00. The field's
 * gameplay meaning is unknown. */
typedef struct {
    unsigned char unknown_0000[0xc9c4];
    int unknown_c9c4;
} OverlayEventStatePrefix;
extern OverlayEventStatePrefix *data_ov039_020bea00;
void func_ov039_020baae0(int value) {
    data_ov039_020bea00->unknown_c9c4 = value;
}
