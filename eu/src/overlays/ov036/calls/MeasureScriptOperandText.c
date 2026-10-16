#include "src/overlays/ov036/Ov036TextWindowState.h"

extern int ByteCode_ResolveOperand(int scriptContext, u16 *operand);
extern int Utf8ToUcs2Bounded(const char *source, u16 *destination, int count);

void MeasureScriptOperandText(Ov036TextWindowSize *outSize, int scriptContext, u16 *operand)
{
    Ov036TextWindowSize size;
    u16 text[0x200];

    Utf8ToUcs2Bounded((const char *)ByteCode_ResolveOperand(scriptContext, operand), text, 0x200);
    MeasureSegmentedTextWindowTiles(&size, 0, text, 0, 0);
    *outSize = size;
}
