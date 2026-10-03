#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 pad_02[0x6];
} ScriptOperand;

typedef struct BoxSize {
    s32 width;
    s32 height;
} BoxSize;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern int func_02025dac(void *vm, ScriptOperand *operand);
extern char *strcat_02021f78(char *dst, const char *src);
extern void Utf8ToUcs2_020512b4(const char *src, u16 *dst, int dstCount);
extern BOOL OpenTextWindowVariant_020c2f88(const BoxSize *boxSize, const u16 *text, s32 optionA, s32 optionB);
extern const char data_ov036_020c383c[];

BOOL ScriptCmd_ShowJoinedMessage_020be1e0(void *vm, ScriptOperand *op)
{
    BoxSize box;
    u16 text[0x200];
    char joined[0x100];
    int i;

    box.width = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    box.height = ScriptVm_ReadOperandInt_02025de4(vm, op++);
    joined[0] = '\0';
    for (i = 0; i < 2; i++) {
        if (op->type == 0) {
            break;
        }
        if (i > 0) {
            strcat_02021f78(joined, data_ov036_020c383c);
        }
        strcat_02021f78(joined, (const char *)func_02025dac(vm, op++));
    }
    Utf8ToUcs2_020512b4(joined, text, 0x200);
    OpenTextWindowVariant_020c2f88(&box, text, ScriptVm_ReadOperandInt_02025de4(vm, op), 0);
    return TRUE;
}
