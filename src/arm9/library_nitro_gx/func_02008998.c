/* Updates tracked OBJ extended-palette bank state, programs E/F/G control registers, and returns other banks to LCDC.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_BeginLoadOBJExtPltt.c.
 * Original routine: GX_BeginLoadOBJExtPltt. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void GX_VRAMCNT_SetLCDC_(u32 bankBits);

struct VRAMState {
    u16 field0;
    u16 pad2;
    u16 pad4;
    u16 pad6;
    u16 pad8;
    u16 fieldA;
};

extern struct VRAMState data_02056f48;

static inline void writeE(u8 v) { *(volatile u8 *)0x04000244 = v; }
static inline void writeF(u8 v) { *(volatile u8 *)0x04000245 = v; }
static inline void writeG(u8 v) { *(volatile u8 *)0x04000246 = v; }

void GX_BeginLoadOBJExtPltt_02008998(int bank) {
    data_02056f48.field0 = (u16)(((data_02056f48.field0 | data_02056f48.fieldA)) & ~bank);
    data_02056f48.fieldA = (u16)bank;
    switch (bank) {
    case 0x00:
        break;
    case 0x60:
        writeG(0x8b);
        /* fallthrough */
    case 0x20:
        writeF(0x83);
        break;
    case 0x40:
        writeG(0x83);
        break;
    case 0x70:
        writeG(0x9b);
        /* fallthrough */
    case 0x30:
        writeF(0x93);
        /* fallthrough */
    case 0x10:
        writeE(0x83);
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_02056f48.field0);
}
