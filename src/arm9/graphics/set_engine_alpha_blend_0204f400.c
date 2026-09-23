/* Sets alpha blend registers on one of two engines according to an object mode field.
 * Evidence: Mode read at +0x4604 and distinct register constants in source.
 * Uncertainty: The mode-to-engine mapping is direct; alpha range depends on caller.
 * Source: src/calls/func_02032798.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void G2x_SetBlendAlpha_(unsigned int reg, int unknownMode0, int unknownMode1, int unknownMode2, int unknownMode3);

void set_engine_alpha_blend_0204f400(char *object, int blendAlpha) {
    if (*(int *)(object + 0x4604) == 2)
        G2x_SetBlendAlpha_(0x04001050, 0, blendAlpha, 0x10, 0);
    else
        G2x_SetBlendAlpha_(0x04000050, 0, blendAlpha, 0x10, 0);
}
