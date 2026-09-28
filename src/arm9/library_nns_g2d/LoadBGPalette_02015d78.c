#include "nitro/types.h"

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

typedef struct NNSG2dPaletteData {
    int fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

typedef struct NNSG2dPaletteCompressInfo {
    u16 numPalette;
    u16 pad16;
    void *pPlttIdxTbl;
} NNSG2dPaletteCompressInfo;

extern u32 data_02055c1c;
extern void DC_FlushRange_0200344c(const void *startAddr, u32 nBytes);
extern void StartHalfwordDmaTransferChecked_02004f6c(u32 dmaNo, const void *src, void *dest, u32 size, int mode);
extern void MIi_CpuCopy16_01ff869c(const void *src, void *dest, u32 size);

static inline void DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size)
{
    if (dmaNo > 3) {
        dmaNo = (u32)~0;
    }
    if (dmaNo != (u32)~0) {
        StartHalfwordDmaTransferChecked_02004f6c(dmaNo, src, dest, size, 1);
    } else {
        MIi_CpuCopy16_01ff869c(src, dest, size);
    }
}

static inline u32 GetPlttSize(const NNSG2dPaletteData *pPltData)
{
    switch (pPltData->fmt) {
    case 3:
        return 0x20;
    case 4:
        return 0x200;
    default:
        break;
    }
    return 0;
}

void LoadBGPalette_02015d78(NNSG2dBGSelect bg, const NNSG2dPaletteData *pPltData,
                            const NNSG2dPaletteCompressInfo *pCmpInfo)
{
    void *pPlttBase;

    DC_FlushRange_0200344c(pPltData->pRawData, pPltData->szByte);
    if (bg <= NNS_G2D_BGSELECT_MAIN3) {
        pPlttBase = (void *)0x05000000;
    } else {
        pPlttBase = (void *)0x05000400;
    }

    if (pCmpInfo != NULL) {
        const u32 szOnePltt = GetPlttSize(pPltData);
        const int numIdx = pCmpInfo->numPalette;
        int i;

        for (i = 0; i < numIdx; i++) {
            const u32 offsetAddr = ((u16 *)pCmpInfo->pPlttIdxTbl)[i] * szOnePltt;
            const void *pSrc = (u8 *)pPltData->pRawData + szOnePltt * i;

            DmaCopy16(data_02055c1c, pSrc, (u8 *)pPlttBase + offsetAddr, szOnePltt);
        }
    } else {
        DmaCopy16(data_02055c1c, pPltData->pRawData, pPlttBase, pPltData->szByte);
    }
}
