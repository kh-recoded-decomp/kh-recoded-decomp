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

typedef struct NNSG2dCharacterData {
    u16 H;
    u16 W;
    int pixelFmt;
    int mappingType;
    u32 characterFmt;
    u32 szByte;
    void *pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dCharacterPosInfo {
    u16 srcPosX;
    u16 srcPosY;
    u16 srcW;
    u16 srcH;
} NNSG2dCharacterPosInfo;

extern volatile u16 *const data_020530d4[];
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

static inline BOOL IsMainBG(NNSG2dBGSelect bg)
{
    return bg <= NNS_G2D_BGSELECT_MAIN3;
}

static inline int GetBGCharOffset(void)
{
    return (int)(0x10000 * ((*(volatile u32 *)0x04000000 & 0x07000000) >> 24));
}

static inline void *GetBGnCharPtr(NNSG2dBGSelect bg)
{
    const int baseBlock = 0x4000 * ((*data_020530d4[bg] & 0x3c) >> 2);

    return (void *)((IsMainBG(bg) ? (0x06000000 + GetBGCharOffset()) : 0x06200000) + baseBlock);
}

static inline void LoadBGnChar(NNSG2dBGSelect bg, const void *pSrc, u32 offset, u32 szByte)
{
    u32 ptr = (u32)GetBGnCharPtr(bg);

    DmaCopy16(data_02055c1c, pSrc, (void *)(ptr + offset), szByte);
}

void LoadBGCharacter_020161c4(NNSG2dBGSelect bg, const NNSG2dCharacterData *pChrData,
                              const NNSG2dCharacterPosInfo *pPosInfo)
{
    u32 offset = 0;

    if (pPosInfo != NULL) {
        int offsetChars = pPosInfo->srcPosY * pPosInfo->srcW;
        u32 szChar = (pChrData->pixelFmt == 4) ? 64 : 32;

        offset = offsetChars * szChar;
    }

    DC_FlushRange_0200344c(pChrData->pRawData, pChrData->szByte);
    LoadBGnChar(bg, pChrData->pRawData, offset, pChrData->szByte);
}
