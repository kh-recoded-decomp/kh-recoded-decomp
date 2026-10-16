#include "src/overlays/ov036/Ov036TextWindowState.h"

extern const char *ScriptVm_ReadTableOffsetPtr(void *vm, void *operand);
extern int Utf8ToUcs2Bounded(const char *source, u16 *destination, int count);

void MeasureScriptTextBox(Ov036TextWindowSize *outSize, void *vm, void *operand)
{
    Ov036TextWindowSize size;
    u16 text[0x200];

    Utf8ToUcs2Bounded(ScriptVm_ReadTableOffsetPtr(vm, operand), text, 0x200);
    MeasureSegmentedTextWindowTiles(&size, 1, text, 0, 0);
    *outSize = size;
}
