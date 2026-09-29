#include "nitro/types.h"

typedef struct {
    s32 (*func)(void *ctx, s32 arg);
    s32 arg;
} ScriptCallback;

typedef struct {
    s32 *script;
    s32 size;
    s32 *code;
    u8 *codeStart;
    u8 *pc;
    u8 *codeEnd;
    s32 unk_18;
    ScriptCallback *current;
    ScriptCallback callbacks[10];
} ScriptFrame;

typedef struct {
    s32 loadedSize;
    ScriptFrame frames[4];
    s32 currentIndex;
} ScriptVm;

extern int FindNameIndexInTable_02025674(s32 *archive, const char *name);
extern s32 *func_0202d3e0(s32 *archive, int recordIndex, int entryIndex);
extern void MI_CpuFill8_01ff8830(void *dest, u8 value, u32 size);

void ScriptVm_PushFrame_0202633c(ScriptVm *vm, s32 *script, s32 size, const char *entryName)
{
    ScriptFrame *frame = &vm->frames[vm->currentIndex + 1];
    s32 *code;
    int entryIndex;

    vm->loadedSize += size;
    frame->size = size;
    frame->script = script;
    if (*script == 0x504b4143) {
        if (entryName != NULL) {
            entryIndex = FindNameIndexInTable_02025674(script, entryName);
        } else {
            entryIndex = 0;
        }
        code = func_0202d3e0(script, 1, entryIndex);
        frame->code = code;
        frame->codeStart = (u8 *)(code + 1);
        frame->pc = (u8 *)(code + 1);
        frame->codeEnd = (u8 *)frame->code + *frame->code;
    } else {
        frame->code = script;
        frame->codeStart = (u8 *)(script + 1);
        frame->pc = (u8 *)(script + 1);
        frame->codeEnd = (u8 *)script + *frame->code;
    }
    frame->unk_18 = 0;
    frame->current = NULL;
    MI_CpuFill8_01ff8830(frame->callbacks, 0, sizeof(frame->callbacks));
    vm->currentIndex++;
}
