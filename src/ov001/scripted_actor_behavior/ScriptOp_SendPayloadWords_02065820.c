#include "nitro/types.h"

typedef struct ScriptOperand {
    u16 type;
    u16 pad_02;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern int ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void func_ov001_02068980(int id, u32 *words, int size);

int ScriptOp_SendPayloadWords_02065820(void *vm, ScriptOperand *operands)
{
    u32 words[128];
    int component;
    int id;
    int count;
    int wordCount;
    int index;
    ScriptOperand *values;

    id = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    count = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    wordCount = 0;
    index = 0;
    values = operands + 2;
    while (index < count) {
        switch (ScriptVm_ReadOperandInt_02025de4(vm, values + index++)) {
        case 0:
            for (component = 0; component < 3; component++) {
                words[wordCount] = ScriptVm_ReadOperandFx32_02025df8(vm, values + index++);
                wordCount++;
            }
            break;
        case 1:
            words[wordCount] = ScriptVm_ReadOperandInt_02025de4(vm, values + index++);
            wordCount++;
            break;
        case 2:
            words[wordCount] = ScriptVm_ReadOperandFx32_02025df8(vm, values + index++);
            wordCount++;
            break;
        }
    }
    func_ov001_02068980(id, words, wordCount * 4);
    return 1;
}
