#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern BOOL IsFieldPanelShown_02071860(void);
extern void func_ov001_02071aac(int page, int mode);
extern void _fp_init_02071aa4(void);
extern void func_ov001_02071cd4(void);
extern void func_ov001_02071be4(void);
extern void func_ov001_02071d6c(int argument);

int ScriptCmd_OpenFieldPanelScreen_0208e7d0(void *context, ScriptOperand *operands)
{
    int screenType;
    int argument;

    screenType = ScriptVm_ReadOperandInt_02025de4(context, operands);
    argument = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    if (!IsFieldPanelShown_02071860()) {
        return 0;
    }
    switch (screenType) {
    case 0:
        switch (argument) {
        case 9:
            func_ov001_02071aac(7, 1);
            break;
        case 8:
            func_ov001_02071aac(8, 2);
            break;
        default:
            func_ov001_02071aac(argument, 0);
            break;
        }
        break;
    case 1:
        _fp_init_02071aa4();
        break;
    case 2:
        func_ov001_02071cd4();
        break;
    case 3:
        func_ov001_02071be4();
        break;
    case 4:
        func_ov001_02071d6c(argument);
        break;
    }
    return 1;
}
