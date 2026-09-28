/* Chooses extended-palette or normal-palette loading for a selected background.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g2d/calls/func_02012de4.c.
 * Original routine: func_02012de4. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef enum {
    GX_TEXFMT_NONE       = 0,
    GX_TEXFMT_A3I5       = 1,
    GX_TEXFMT_PLTT4      = 2,
    GX_TEXFMT_PLTT16     = 3,
    GX_TEXFMT_PLTT256    = 4,
    GX_TEXFMT_COMP4x4    = 5,
    GX_TEXFMT_A5I3       = 6,
    GX_TEXFMT_DIRECT     = 7
} GXTexFmt;
typedef struct NNSG2dPaletteCompressInfo {
    u16 numPalette;
    u16 pad16;
    void * pPlttIdxTbl;
} NNSG2dPaletteCompressInfo;
typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void * pRawData;
} NNSG2dPaletteData;
typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3,
    NNS_G2D_BGSELECT_NUM
} NNSG2dBGSelect;
typedef enum NNSG2dBGExtPlttSlot {
    NNS_G2D_BGEXTPLTTSLOT_MAIN0,
    NNS_G2D_BGEXTPLTTSLOT_MAIN1,
    NNS_G2D_BGEXTPLTTSLOT_MAIN2,
    NNS_G2D_BGEXTPLTTSLOT_MAIN3,
    NNS_G2D_BGEXTPLTTSLOT_SUB0,
    NNS_G2D_BGEXTPLTTSLOT_SUB1,
    NNS_G2D_BGEXTPLTTSLOT_SUB2,
    NNS_G2D_BGEXTPLTTSLOT_SUB3
} NNSG2dBGExtPlttSlot;
extern void func_02015c48 (NNSG2dBGExtPlttSlot slot, const NNSG2dPaletteData * pPltData, const NNSG2dPaletteCompressInfo * pCmpInfo);
extern void func_02015d78 (NNSG2dBGSelect bg, const NNSG2dPaletteData * pPltData, const NNSG2dPaletteCompressInfo * pCmpInfo);
extern NNSG2dBGExtPlttSlot func_02015ea4 (NNSG2dBGSelect bg);

/* G2D_LoadBackgroundPalette_0201611c -- NitroSystem g2d_Screen.c: LoadBGPaletteSelect. */
void G2D_LoadBackgroundPalette_0201611c (NNSG2dBGSelect bg, BOOL bToExtPltt, const NNSG2dPaletteData * pPltData, const NNSG2dPaletteCompressInfo * pCmpInfo)
{

    if (bToExtPltt) {
        NNSG2dBGExtPlttSlot slot = func_02015ea4(bg);
        func_02015c48(slot, pPltData, pCmpInfo);
    } else {
        func_02015d78(bg, pPltData, pCmpInfo);
    }
}
