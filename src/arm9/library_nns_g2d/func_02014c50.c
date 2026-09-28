/* Resolves the cell array, per-cell OAM arrays, optional VRAM-transfer data and extended cell attributes in a loaded resource.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g2d/calls/func_020118ec.c.
 * Original routine: func_020118ec. External references are
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

#define NNS_G2D_UNPACK_OFFSET_PTR(ptr, baseOffs) (ptr) = (void *)((u32)(ptr) + (u32)baseOffs)

typedef enum NNSG2dCharacterDataMappingType {
    NNS_G2D_CHARACTERMAPPING_1D_32,
    NNS_G2D_CHARACTERMAPPING_1D_64,
    NNS_G2D_CHARACTERMAPPING_1D_128,
    NNS_G2D_CHARACTERMAPPING_1D_256,
    NNS_G2D_CHARACTERMAPPING_2D,
    NNS_G2D_CHARACTERMAPPING_MAX
} NNSG2dCharacterDataMappingType;
typedef struct NNSG2dCellVramTransferData {
    u32 srcDataOffset;
    u32 szByte;
} NNSG2dCellVramTransferData;
typedef struct NNSG2dVramTransferData {
    u32 szByteMax;
    NNSG2dCellVramTransferData * pCellTransferDataArray;
} NNSG2dVramTransferData;
typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;
typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData * pOamAttrArray;
} NNSG2dCellData;
typedef struct NNSG2dCellDataBank {
    u16 numCells;
    u16 cellBankAttr;
    NNSG2dCellData * pCellDataArrayHead;
    NNSG2dCharacterDataMappingType mappingMode;
    NNSG2dVramTransferData * pVramTransferData;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dCellDataBank;
const NNSG2dCellData * func_02014c28(const NNSG2dCellDataBank * pCellData, u16 idx);
extern void * func_02014bc0 (NNSG2dCellDataBank * pCellBank);
extern void func_02014bdc (void * pExData);
extern const NNSG2dCellData * func_02014c28 (const NNSG2dCellDataBank * pCellData, u16 idx);

/* G2D_UnpackCellBank_02014c50 -- NitroSystem g2d_NOB_load.c: NNS_G2dUnpackNCE. */
void G2D_UnpackCellBank_02014c50 (NNSG2dCellDataBank * pCellData)
{
    {
        pCellData->pCellDataArrayHead = NNS_G2D_UNPACK_OFFSET_PTR(pCellData->pCellDataArrayHead, pCellData);

        {
            void * pHeadOfOAMData = func_02014bc0(pCellData);

            u16 i;
            NNSG2dCellData * pCell = NULL;
            for (i = 0; i < pCellData->numCells; i++) {
                pCell = (NNSG2dCellData *)(func_02014c28(pCellData, i));
                pCell->pOamAttrArray = NNS_G2D_UNPACK_OFFSET_PTR(pCell->pOamAttrArray, pHeadOfOAMData);
            }
        }

        if (pCellData->pVramTransferData != NULL) {
            NNSG2dVramTransferData * pVramTsfmData = NNS_G2D_UNPACK_OFFSET_PTR(pCellData->pVramTransferData, pCellData);

            pVramTsfmData->pCellTransferDataArray = NNS_G2D_UNPACK_OFFSET_PTR(pVramTsfmData->pCellTransferDataArray, pVramTsfmData);
            pCellData->pVramTransferData = pVramTsfmData;
        }

        if (pCellData->pExtendedData != NULL) {
            pCellData->pExtendedData = NNS_G2D_UNPACK_OFFSET_PTR(pCellData->pExtendedData, pCellData);
            func_02014bdc(pCellData->pExtendedData);
        }

    }

}
