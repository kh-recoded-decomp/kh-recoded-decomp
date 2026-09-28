/* Decodes a memory-block header into containing base and payload pointers.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/auto/GetRegionOfMBlock.c.
 * Original routine: GetRegionOfMBlock. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
void DecodeMemoryBlockRegion_02012bd0(void **out, char *node)
{
    unsigned short offset = (*(unsigned short *)(node + 2) >> 8) & 0x7f;
    char *base = node + 0x10;

    out[0] = node - offset;
    out[1] = (void *)(*(int *)(node + 4) + (int)base);
}
