#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_01;
    u16 currentValue;
    u16 savedValue;
} OverlaySelectionRecord;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);

int ScriptCmd_RestoreSelectionRecordValue_02065f8c(void *context, ScriptOperand *operands)
{
    u32 selectionIndex;

    selectionIndex = ScriptVm_ReadOperandInt_02025de4(context, operands);
    GetOverlaySelectionRecord_0204f768(selectionIndex)->currentValue =
        GetOverlaySelectionRecord_0204f768(selectionIndex)->savedValue;
    return 1;
}
