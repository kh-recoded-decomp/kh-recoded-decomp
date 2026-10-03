#include "nitro/types.h"

typedef struct TextBoxSize {
    s32 width;
    s32 height;
} TextBoxSize;

extern int func_02025dac(int scriptCtx, unsigned short *operand);
extern int Utf8ToUcs2Bounded_020bda5c(const char *src, u16 *dst, int dstCount);
extern void func_ov036_020c2b7c(TextBoxSize *outSize, int screen, const u16 *text, int padX, int padY);

void MeasureScriptOperandText_020bdb5c(TextBoxSize *outSize, int scriptCtx, unsigned short *operand)
{
    TextBoxSize size;
    u16 text[0x200];

    Utf8ToUcs2Bounded_020bda5c((const char *)func_02025dac(scriptCtx, operand), text, 0x200);
    func_ov036_020c2b7c(&size, 0, text, 0, 0);
    *outSize = size;
}
