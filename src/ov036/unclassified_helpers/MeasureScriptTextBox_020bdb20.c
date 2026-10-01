#include "nitro/types.h"

typedef struct TextBoxSize {
    s32 width;
    s32 height;
} TextBoxSize;

extern const char *func_ov036_020bdb00(void *vm, void *operand);
extern int Utf8ToUcs2Bounded_020bda5c(const char *src, u16 *dst, int dstCount);
extern void func_ov036_020c2b7c(TextBoxSize *outSize, int screen, const u16 *text, int padX, int padY);

void MeasureScriptTextBox_020bdb20(TextBoxSize *outSize, void *vm, void *operand)
{
    TextBoxSize size;
    u16 text[0x200];

    Utf8ToUcs2Bounded_020bda5c(func_ov036_020bdb00(vm, operand), text, 0x200);
    func_ov036_020c2b7c(&size, 1, text, 0, 0);
    *outSize = size;
}
