/* Copies a clipped rectangular area of screen data, adjusting coordinates and strides.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_02013484.c.
 * Original routine: func_02013484. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned short u16;
typedef unsigned long u32;

typedef enum NNSG2dScreenFormat {
    NNS_G2D_SCREENFORMAT_TEXT,
    NNS_G2D_SCREENFORMAT_AFFINE,
    NNS_G2D_SCREENFORMAT_AFFINEEXT
} NNSG2dScreenFormat;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

extern void func_020163fc(void *pScreenDst,
                          const NNSG2dScreenData *pScreenData,
                          int srcX, int srcY, int dstX, int dstY,
                          int dstW, int dstH, int width, int height);
extern void func_02016624(void *pScreenDst,
                          const NNSG2dScreenData *pScreenData,
                          int srcX, int srcY, int dstX, int dstY,
                          int dstW, int width, int height);
extern void func_0201668c(void *pScreenDst,
                          const NNSG2dScreenData *pScreenData,
                          int srcX, int srcY, int dstX, int dstY,
                          int dstW, int width, int height);

void CopyClippedScreenRegion_020167d0(void *pScreenDst,
                   const NNSG2dScreenData *pScreenData,
                   int srcX, int srcY, int dstX, int dstY,
                   int dstW, int dstH, int width, int height)
{
    if (dstX < 0) {
        const int adj = -dstX;
        srcX += adj;
        width -= adj;
        dstX = 0;
    }
    if (dstY < 0) {
        const int adj = -dstY;
        srcY += adj;
        height -= adj;
        dstY = 0;
    }
    if (dstX + width > dstW) {
        const int adj = (dstX + width) - dstW;
        width -= adj;
    }
    if (dstY + height > dstH) {
        const int adj = (dstY + height) - dstH;
        height -= adj;
    }
    if (srcX < 0) {
        const int adj = -srcX;
        dstX += adj;
        width -= adj;
        srcX = 0;
    }
    if (srcY < 0) {
        const int adj = -srcY;
        dstY += adj;
        height -= adj;
        srcY = 0;
    }
    if (srcX + width > pScreenData->screenWidth / 8) {
        const int adj = (srcX + width) - (pScreenData->screenWidth / 8);
        width -= adj;
    }
    if (srcY + height > pScreenData->screenHeight / 8) {
        const int adj = (srcY + height) - (pScreenData->screenHeight / 8);
        height -= adj;
    }

    if (width <= 0 || height <= 0) {
        return;
    }

    switch (pScreenData->screenFormat) {
    case NNS_G2D_SCREENFORMAT_TEXT:
        func_020163fc(pScreenDst, pScreenData,
                      srcX, srcY, dstX, dstY, dstW, dstH, width, height);
        break;
    case NNS_G2D_SCREENFORMAT_AFFINE:
        func_02016624(pScreenDst, pScreenData,
                      srcX, srcY, dstX, dstY, dstW, width, height);
        break;
    case NNS_G2D_SCREENFORMAT_AFFINEEXT:
        func_0201668c(pScreenDst, pScreenData,
                      srcX, srcY, dstX, dstY, dstW, width, height);
        break;
    default:
        break;
    }
}
