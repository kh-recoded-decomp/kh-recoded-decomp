#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 pad_02[0x6];
} ScriptOperand;

typedef struct BoxSize {
    s32 width;
    s32 height;
} BoxSize;

typedef struct NameTable {
    u8 unknown_00[0x70];
    const char *names[16];
} NameTable;

typedef struct ScriptVm {
    u8 unknown_000[0x1c8];
    NameTable *nameTable;
    u8 unknown_1cc[0x628 - 0x1cc];
    int busy;
} ScriptVm;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptVm *vm, ScriptOperand *operand);
extern void ScriptCmd_SetElemField_02025e18(ScriptVm *vm, ScriptOperand *operand);
extern char *strcat_02021f78(char *dst, const char *src);
extern void Utf8ToUcs2_020512b4(const char *src, u16 *dst, int dstCount);
extern BOOL OpenTextWindowVariant_020c2f88(const BoxSize *boxSize, const u16 *text, s32 optionA, s32 optionB);
extern BOOL func_ov001_020645c8(u32 value);
extern const char data_ov036_020c383c[];
extern const char data_ov036_020c3840[];

BOOL ScriptCmd_ShowNameList_020be3ac(ScriptVm *vm, ScriptOperand *op)
{
    BoxSize box;
    u16 text[0x200];
    char joined[0x100];
    int i;

    if (vm->busy != 0) {
        return TRUE;
    }
    box.width = ScriptVm_ReadOperandInt_02025de4(vm, op);
    box.height = ScriptVm_ReadOperandInt_02025de4(vm, op + 1);
    joined[0] = '\0';
    for (i = 0; i < 16; i++) {
        if (vm->nameTable->names[i] == NULL) {
            break;
        }
        if (i > 0) {
            strcat_02021f78(joined, data_ov036_020c383c);
        }
        if (func_ov001_020645c8(i + 0x3700)) {
            strcat_02021f78(joined, vm->nameTable->names[i]);
        } else {
            strcat_02021f78(joined, data_ov036_020c3840);
        }
    }
    Utf8ToUcs2_020512b4(joined, text, 0x200);
    OpenTextWindowVariant_020c2f88(&box, text, 0, 0);
    ScriptCmd_SetElemField_02025e18(vm, op);
    return FALSE;
}
