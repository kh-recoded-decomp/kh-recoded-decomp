/* Encodes signed master brightness into the brightness register as brighten, darken, or off.
 * The exact public SDK symbol is not established from the body, so the target address-based name is retained; behavior is limited to the implemented operation. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/GXx_SetMasterBrightness_.c.
 * Original routine: GXx_SetMasterBrightness_. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
void func_02006748(unsigned short *dst, int value)
{
    if (value == 0) {
        *dst = 0;
    } else if (value > 0) {
        *dst = value | 0x4000;
    } else {
        *dst = -value | 0x8000;
    }
}
