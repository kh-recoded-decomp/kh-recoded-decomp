typedef struct {
    unsigned char unknown_0000[0xc9c4];
    int unknown_c9c4;
} OverlayEventStatePrefix;
extern OverlayEventStatePrefix *data_ov039_020bea00;
void func_ov039_020baae0(int value) {
    data_ov039_020bea00->unknown_c9c4 = value;
}
