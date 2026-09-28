/* Reads position/vector-matrix stack level from GXSTAT and reports the stack-error bit.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G3X_GetMtxStackLevelPV.c.
 * Original routine: G3X_GetMtxStackLevelPV. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Reads the matrix-stack level out of GXSTAT; -1 if the stack-error bit is set. */
int G3X_GetMtxStackLevelPV_02006ce4(int *level) {
    if ((*(volatile unsigned *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned *)0x04000600 & 0x1f00) >> 8;
    return 0;
}
