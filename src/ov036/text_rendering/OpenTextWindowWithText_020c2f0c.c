#include "nitro/types.h"

typedef struct TextWindowRequest {
    s32 posX;
    s32 posY;
    const s32 *boxSize;
    s32 style;
    const u16 *text;
    s32 optionA;
    s32 optionB;
    s32 unused;
} TextWindowRequest;

extern void func_ov036_020c2890(TextWindowRequest *request);

BOOL OpenTextWindowWithText_020c2f0c(s32 posX, s32 posY, const s32 *boxSize, s32 style, const u16 *text)
{
    TextWindowRequest request;

    request.posX = posX;
    request.posY = posY;
    request.boxSize = boxSize;
    request.style = style;
    request.text = text;
    request.optionA = 0;
    request.optionB = 0;
    func_ov036_020c2890(&request);
    return TRUE;
}
