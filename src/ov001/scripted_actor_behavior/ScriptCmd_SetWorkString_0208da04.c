#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptWork {
    u8 pad_00[0x70];
    char *strings[16];
} ScriptWork;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptWork *work;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern const char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern char *strcpy_02021e60(char *dst, const char *src);

int ScriptCmd_SetWorkString_0208da04(ScriptContext *context, ScriptOperand *operands)
{
    int slot;
    const char *text;

    slot = ScriptVm_ReadOperandInt_02025de4(context, operands);
    text = func_02025dac(context, operands + 1);
    if (context->work->strings[slot] == NULL) {
        context->work->strings[slot] = NNSi_FndAllocFromDefaultHeap_0202a178(0x40);
        func_01ff8830(context->work->strings[slot], 0, 0x40);
    }
    strcpy_02021e60(context->work->strings[slot], text);
    return 1;
}
