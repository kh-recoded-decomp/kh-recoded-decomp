#include "libs/nns/g2d/include/g2d_charcanvas_internal.h"

static inline const NNSiG2dObjectSize *GetMaxObjectSize(int width, int height)
{
    int logWidth = width >= 8 ? 3 : NNSi_G2dIntegerLog2((u32)width);
    int logHeight = height >= 8 ? 3 : NNSi_G2dIntegerLog2((u32)height);
    return &sMaxObjectSizeTable[logHeight][logWidth];
}

u32 GetCharIndex1D(u32 charX, u32 charY, u32 areaWidth, u32 areaHeight,
                   u32 objectWidthShift, u32 objectHeightShift)
{
    const u32 fullBits = ~0U;
    u32 index = 0;

    for (;;) {
        const u32 objectWidthMaskInv = fullBits << objectWidthShift;
        const u32 objectHeightMaskInv = fullBits << objectHeightShift;
        const u32 alignedWidth = areaWidth & objectWidthMaskInv;
        const u32 alignedHeight = areaHeight & objectHeightMaskInv;

        if (alignedHeight <= charY) {
            index += areaWidth * alignedHeight;
            if (alignedWidth <= charX) {
                index += (areaHeight - alignedHeight) * alignedWidth;
                charX -= alignedWidth;
                charY -= alignedHeight;
                areaWidth -= alignedWidth;
                areaHeight -= alignedHeight;
            } else {
                charY -= alignedHeight;
                areaWidth = alignedWidth;
                areaHeight -= alignedHeight;
            }
        } else {
            const u32 objectHeightMask = ~objectHeightMaskInv;
            if (alignedWidth <= charX) {
                index += alignedWidth * alignedHeight;
                charX -= alignedWidth;
                areaWidth -= alignedWidth;
                areaHeight = alignedHeight;
            } else {
                const u32 objectWidthMask = ~objectWidthMaskInv;
                index += (charY & objectHeightMaskInv) * alignedWidth;
                index += (charX & objectWidthMaskInv) << objectHeightShift;
                index += (charY & objectHeightMask) << objectWidthShift;
                index += charX & objectWidthMask;
                return index;
            }
        }

        {
            const NNSiG2dObjectSize *objectSize =
                GetMaxObjectSize((int)areaWidth, (int)areaHeight);
            objectWidthShift = objectSize->widthShift;
            objectHeightShift = objectSize->heightShift;
        }
    }
}
