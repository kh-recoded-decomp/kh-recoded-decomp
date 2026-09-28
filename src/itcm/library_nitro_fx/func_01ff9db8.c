/* Waits for the square-root unit and returns its rounded fixed-point result.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/FX_GetSqrtResult.c.
 * Original routine: FX_GetSqrtResult. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Spins on the SQRTCNT busy bit, then rounds SQRT_RESULT to fx32 (0x200 = half a unit). */
unsigned FX_GetSqrtResult_01ff9db8(void) {
    while (*(volatile unsigned short *)0x040002b0 & 0x8000) {
    }
    return (*(volatile unsigned *)0x040002b4 + 0x200) >> 10;
}
