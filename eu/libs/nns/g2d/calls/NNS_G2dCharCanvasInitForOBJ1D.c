#include "libs/nns/g2d/include/g2d_charcanvas_internal.h"

typedef union NNSiG2dOBJ1DParam {
    u32 packed;
    struct {
        unsigned baseWidthShift : 8;
        unsigned baseHeightShift : 8;
    } fields;
} NNSiG2dOBJ1DParam;

extern const NNSiG2dCharCanvasVTable VTABLE_OBJ1D;
extern void InitCharCanvas(NNSG2dCharCanvas *canvas, void *charBase,
                           int areaWidth, int areaHeight, int colorMode,
                           const NNSiG2dCharCanvasVTable *vtable, u32 param);

static inline const NNSiG2dObjectSize *GetMaxObjectSize(int width, int height)
{
    int logWidth = width >= 8 ? 3 : NNSi_G2dIntegerLog2((u32)width);
    int logHeight = height >= 8 ? 3 : NNSi_G2dIntegerLog2((u32)height);
    return &sMaxObjectSizeTable[logHeight][logWidth];
}

void NNS_G2dCharCanvasInitForOBJ1D(NNSG2dCharCanvas *canvas, void *charBase,
                                    int areaWidth, int areaHeight,
                                    int colorMode)
{
    NNSiG2dOBJ1DParam param;
    const NNSiG2dObjectSize *objectSize =
        GetMaxObjectSize(areaWidth, areaHeight);

    param.fields.baseWidthShift = objectSize->widthShift;
    param.fields.baseHeightShift = objectSize->heightShift;
    InitCharCanvas(canvas, charBase, areaWidth, areaHeight, colorMode,
                   &VTABLE_OBJ1D, param.packed);
}
