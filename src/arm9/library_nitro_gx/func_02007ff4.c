typedef unsigned short u16;
typedef unsigned int u32;
typedef int GXVRamTex;

extern GXVRamTex SNDi_UnlockMutex(void);
#define GX_ResetBankForTex SNDi_UnlockMutex

extern const struct {
    u16 blk1;
    u16 blk2;
    u16 szBlk1;
} data_02052904[16];
#define sTexStartAddrTable data_02052904

extern struct {
    u32 pad0;
    u32 sTexLCDCBlk1;
    u32 sTexPlttLCDCBlk;
    int sTexPltt;
    u32 pad10;
    GXVRamTex sTex;
    u32 sTexLCDCBlk2;
    u32 sSzTexBlk1;
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
