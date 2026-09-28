/* Resets texture-bank mapping and records texture block addresses and size for loading.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_BeginLoadTex.c.
 * Original routine: GX_BeginLoadTex. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* NitroSDK gx_load3d.c: GX_BeginLoadTex_02007ff4 -- release the texture banks to LCDC and record, from
 * sTexStartAddrTable, the LCDC addresses of the (up to two) blocks the bank mask maps to and the
 * size of the first one. The symbol map calls GX_ResetBankForTex "SNDi_UnlockMutex". */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int GXVRamTex;

extern GXVRamTex SNDi_UnlockMutex(void);   /* GX_ResetBankForTex */
#define GX_ResetBankForTex SNDi_UnlockMutex

/* gx_load3d.c's texture start table (data_02052904): blk1 / blk2 / szBlk1, each >> 12. */
extern const struct {
    u16 blk1;
    u16 blk2;
    u16 szBlk1;
} data_02052904[16];
#define sTexStartAddrTable data_02052904

/* gx_load3d.c statics, one .bss block (data_02056f28): the texture / texture-palette upload state. */
extern struct {
    u32 pad0;                     /* 0x00 */
    u32 sTexLCDCBlk1;             /* 0x04 */
    u32 sTexPlttLCDCBlk;          /* 0x08 */
    int sTexPltt;                 /* 0x0c */
    u32 pad10;                    /* 0x10 */
    GXVRamTex sTex;               /* 0x14 */
    u32 sTexLCDCBlk2;             /* 0x18 */
    u32 sSzTexBlk1;               /* 0x1c */
} data_02056f28;
#define sTexLCDCBlk1 data_02056f28.sTexLCDCBlk1
#define sTex data_02056f28.sTex
#define sTexLCDCBlk2 data_02056f28.sTexLCDCBlk2
#define sSzTexBlk1 data_02056f28.sSzTexBlk1

void GX_BeginLoadTex_02007ff4(void)
{
    sTex = GX_ResetBankForTex();

    sTexLCDCBlk1 = (u32)(sTexStartAddrTable[sTex].blk1 << 12);
    sTexLCDCBlk2 = (u32)(sTexStartAddrTable[sTex].blk2 << 12);
    sSzTexBlk1 = (u32)(sTexStartAddrTable[sTex].szBlk1 << 12);
}
