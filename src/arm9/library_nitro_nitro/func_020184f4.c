/* For tags M, J or V, computes a four-byte-aligned size from header byte 0x18 or 0x17; returns zero for null inputs or other tags.
 * Uncertainty: The record/tag meaning and its game-facing role remain unknown. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nitro/calls/NTRi_GetRegionTableSize.c.
 * Original routine: NTRi_GetRegionTableSize. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
struct H {
    char _0[0x17];
    unsigned char x17;
    unsigned char x18;
};

int func_020184f4(const unsigned char *region, struct H *hdr)
{
    int v;
    if (region == 0 || hdr == 0) return 0;
    switch (*region) {
    case 'M':
        v = hdr->x18 << 1;
        return (v + 0x1c) & ~3;
    case 'J':
    case 'V':
        v = hdr->x17 << 1;
        return (v + 0x1c) & ~3;
    }
    return 0;
}
