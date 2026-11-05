extern void *G2x_SetBlendBrightness_();

void *SetScrollMainBlendBrightness(int this_, int arg1) {
    return G2x_SetBlendBrightness_(0x04000050, this_, arg1);
}
