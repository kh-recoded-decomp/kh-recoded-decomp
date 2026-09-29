#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern BOOL IsCounterNegative_020c0708(void);
extern void func_ov001_02071b7c(void);
extern void _fp_init_02071aa8(void);
extern void *PXI_Init_02071d64(void);
extern void *PXI_Init_02071ccc(void);
extern void *PXI_Init_02071de8(void);

int ScriptCmd_CloseFieldPanelScreen_0208e848(void *context, ScriptOperand *operands)
{
    if (IsCounterNegative_020c0708()) {
        switch (ScriptVm_ReadOperandInt_02025de4(context, operands)) {
        case 0:
            func_ov001_02071b7c();
            break;
        case 1:
            _fp_init_02071aa8();
            break;
        case 2:
            PXI_Init_02071d64();
            break;
        case 3:
            PXI_Init_02071ccc();
            break;
        case 4:
            PXI_Init_02071de8();
            break;
        }
        return 1;
    }
    return 0;
}
