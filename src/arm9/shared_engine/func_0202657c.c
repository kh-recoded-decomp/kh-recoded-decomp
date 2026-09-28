#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad2;
    s32 payload;
} ScriptOperand;

typedef struct ScriptObj {
    u8 pad_00[0x1cc];
    s32 armed;
    s32 valueA;
    s32 valueB;
    char text[0x40];
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *obj, void *cmd);
extern ScriptOperand *ScriptVm_ResolveOperand_02025d08(void *obj, void *cmd);
extern int func_02025dac(void *obj, void *operand);
extern char *strncpy_02021f28(char *dst, const char *src, unsigned int n);

int func_0202657c(ScriptObj *obj, ScriptOperand *cmd)
{
    ScriptOperand *resolved = ScriptVm_ResolveOperand_02025d08(obj, cmd + 2);

    obj->valueA = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    obj->valueB = ScriptVm_ReadOperandInt_02025de4(obj, cmd + 1);

    if (resolved->type == 0) {
        obj->text[0] = 0;
    } else {
        char *src = (char *)func_02025dac(obj, resolved);
        strncpy_02021f28(obj->text, src, 0x3f);
        obj->text[0x3f] = 0;
    }

    obj->armed = 0;
    return 3;
}
