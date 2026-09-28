#include "nitro/types.h"

typedef enum NNS_G2D_VRAM_TYPE {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB = 2
} NNS_G2D_VRAM_TYPE;

typedef struct NNSG2dPaletteData {
    int fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

typedef struct NNSG2dImagePaletteProxy {
    int fmt;
    BOOL bExtendedPlt;
    u32 vramLocation[3];
} NNSG2dImagePaletteProxy;

extern void DC_FlushRange_0200344c(const void *startAddr, u32 nBytes);
extern void GX_BeginLoadTexPltt_020081e0(void);
extern void GX_LoadTexPltt_02008214(const void *src, u32 offset, u32 size);
extern void GX_EndLoadTexPltt_02008284(void);
extern void GX_LoadOBJPltt_02007310(const void *src, u32 offset, u32 size);
extern void GX_BeginLoadOBJExtPltt_02007d90(void);
extern void GX_LoadOBJExtPltt_02007dd8(const void *src, u32 offset, u32 size);
extern void GX_EndLoadOBJExtPltt_02007e48(void);
extern void GXS_LoadOBJPltt_0200736c(const void *src, u32 offset, u32 size);
extern void GXS_BeginLoadOBJExtPltt_02007f3c(void);
extern void GXS_LoadOBJExtPltt_02007f54(const void *src, u32 offset, u32 size);
extern void GXS_EndLoadOBJExtPltt_02007fbc(void);
extern void NNS_G2dSetImagePaletteProxyAddr_020152d8(NNSG2dImagePaletteProxy *pProxy, NNS_G2D_VRAM_TYPE type, u32 addr);

void NNS_G2dLoadPalette_020154fc(const NNSG2dPaletteData *pSrcData, u32 addr, NNS_G2D_VRAM_TYPE type,
                                 NNSG2dImagePaletteProxy *pPltProxy)
{
    void *pData = pSrcData->pRawData;
    u32 szByte = pSrcData->szByte;

    DC_FlushRange_0200344c(pData, szByte);
    switch (type) {
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        if (pSrcData->bExtendedPlt != 0) {
            GX_BeginLoadOBJExtPltt_02007d90();
            GX_LoadOBJExtPltt_02007dd8(pData, addr, szByte);
            GX_EndLoadOBJExtPltt_02007e48();
        } else {
            GX_LoadOBJPltt_02007310(pData, addr, szByte);
        }
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        if (pSrcData->bExtendedPlt != 0) {
            GXS_BeginLoadOBJExtPltt_02007f3c();
            GXS_LoadOBJExtPltt_02007f54(pData, addr, szByte);
            GXS_EndLoadOBJExtPltt_02007fbc();
        } else {
            GXS_LoadOBJPltt_0200736c(pData, addr, szByte);
        }
        break;
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        GX_BeginLoadTexPltt_020081e0();
        GX_LoadTexPltt_02008214(pData, addr, szByte);
        GX_EndLoadTexPltt_02008284();
        break;
    }
    pPltProxy->fmt = pSrcData->fmt;
    pPltProxy->bExtendedPlt = pSrcData->bExtendedPlt;
    NNS_G2dSetImagePaletteProxyAddr_020152d8(pPltProxy, type, addr);
}
