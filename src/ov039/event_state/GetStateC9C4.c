/* Paired with 020baae0: reads the shared ov039 state word at +0xc9c4.
 * The field's gameplay meaning is unknown. */
typedef struct {
    unsigned char unknown_0000[0xc9c4];
    int unknown_c9c4;
} OverlayEventStatePrefix;
extern OverlayEventStatePrefix *data_ov039_020bea00;
int GetStateC9C4(void) { return data_ov039_020bea00->unknown_c9c4; }
