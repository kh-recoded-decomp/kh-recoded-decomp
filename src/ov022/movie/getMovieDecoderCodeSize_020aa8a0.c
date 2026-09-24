/* Returns the byte size of the embedded movie decoder code.
 * Evidence: The related movie routine uses this same constant as the decoder-code copy size.
 * Uncertainty: The constant is known; exact decoder implementation details are outside this helper.
 * Source: khdays-decomp/src/overlays/ov024/auto/func_ov024_020865c4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int getMovieDecoderCodeSize_020aa8a0(void)
{
    return 0x659c;
}
