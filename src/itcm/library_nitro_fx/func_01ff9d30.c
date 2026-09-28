/* Waits for the divider and returns the 64-bit quotient register.
 * The exact public SDK symbol is not established from the body, so the target address-based name is retained; behavior is limited to the implemented operation. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/func_01ff8ab0.c.
 * Original routine: func_01ff8ab0. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Waits for the hardware divider to finish (DIVCNT busy bit), then reads the
 * 64-bit quotient from DIV_RESULT (0x040002a0). */
long long func_01ff9d30(void) {
    volatile unsigned short *reg_divcnt = (volatile unsigned short *)0x04000280;
    while (*reg_divcnt & 0x8000)
        ;
    return *(long long *)0x040002a0;
}
