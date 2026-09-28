/* Finds the screen-data block in a binary resource and returns its payload or a null result.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g2d/calls/func_02011a6c.c.
 * Original routine: func_02011a6c. External references are
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

#define NNS_G2D_BINBLK_SIG_SCRDATA (u32)'SCRN'

typedef struct NNSG2dBinaryFileHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} NNSG2dBinaryFileHeader;
typedef struct NNSG2dBinaryBlockHeader {
    u32 kind;
    u32 size;
} NNSG2dBinaryBlockHeader;
typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;
typedef struct NNSG2dScreenDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dScreenData screenData;
} NNSG2dScreenDataBlock;
NNSG2dBinaryBlockHeader * func_02014e00(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);

/* G2D_GetScreenFromFile_02014dd0 -- NitroSystem g2d_NSC_load.c: NNS_G2dGetUnpackedScreenData. */
BOOL G2D_GetScreenFromFile_02014dd0 (void * pNscrFile, NNSG2dScreenData ** ppScrData)
{

    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNscrFile;
        {
            NNSG2dScreenDataBlock * pBinBlk =
                (NNSG2dScreenDataBlock *)func_02014e00(pBinFile,
                                                                NNS_G2D_BINBLK_SIG_SCRDATA);
            if (pBinBlk) {

                *ppScrData = &(pBinBlk->screenData);

                return TRUE;
            } else {
                *ppScrData = NULL;
                return FALSE;

            }
        }
    }
}
