/* Marks a cell transfer as requested and stores its source offset and byte count.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g2d/calls/func_0201285c.c.
 * Original routine: func_0201285c. External references are
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




typedef enum NNS_G2D_VRAM_TYPE {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB  = 2,
    NNS_G2D_VRAM_TYPE_2DBOTH = 3,
    NNS_G2D_VRAM_TYPE_MAX    = 3
} NNS_G2D_VRAM_TYPE;
typedef struct NNSG2dVRamLocation {
    u32 baseAddrOfVram[NNS_G2D_VRAM_TYPE_MAX];
} NNSG2dVRamLocation;
typedef struct NNSG2dCellTransferState {
    NNSG2dVRamLocation dstVramLocation;
    u32 szDst;
    const void * pSrcNCGR;
    const void * pSrcNCBR;
    u32 szSrcData;
    BOOL bActive;
    u32 bDrawn;
    u32 bTransferRequested;
    u32 srcOffset;
    u32 szByte;
} NNSG2dCellTransferState;
NNSG2dCellTransferState * func_02015b60(u32 handle);
extern NNSG2dCellTransferState * func_02015b60 (u32 handle);

/* G2D_RequestCellTransfer_02015b78 -- NitroSystem g2d_CellTransferManager.c: NNS_G2dSetCellTransferStateRequested. */
void G2D_RequestCellTransfer_02015b78 (u32 handle, u32 srcOffset, u32 szByte)
{

    {
        NNSG2dCellTransferState * pState = func_02015b60(handle);


        pState->bTransferRequested = 0xFFFFFFFF;
        pState->srcOffset = srcOffset;
        pState->szByte = szByte;
    }
}
