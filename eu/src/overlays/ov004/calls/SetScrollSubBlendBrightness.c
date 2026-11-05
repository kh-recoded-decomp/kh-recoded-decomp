extern void *G2x_SetBlendBrightness_();

void *SetScrollSubBlendBrightness(int this_, int arg1) {
    return G2x_SetBlendBrightness_(0x04001050, this_, arg1);
}
