/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/calls/OS_GetTickLo.c. */
/* OS_GetTickLo: reads the low 16 bits of the tick timer (TM0CNT_L, 0x04000100). */

int OS_GetTickLo(void) {
    return *(volatile unsigned short *)0x04000100;
}
