/* Releases texture-palette banks for transfer and records their LCDC destination address.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_BeginLoadTexPltt.c.
 * Original routine: GX_BeginLoadTexPltt. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Releases the texture-palette banks and records both the released mask and the base
 * address the slot table maps it to. */
extern int func_02008d38(void);
extern int data_02056f28[];
extern unsigned short data_020528f4[];

void GX_BeginLoadTexPltt_020081e0(void) {
    int mask = func_02008d38();
    data_02056f28[3] = mask;
    data_02056f28[2] = data_020528f4[mask >> 4] << 12;
}
