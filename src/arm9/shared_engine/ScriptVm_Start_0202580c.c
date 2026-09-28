#include "nitro/types.h"

typedef struct ScriptSlot {
    void *fn;
    s32 arg;
} ScriptSlot;

typedef struct ScriptFrame {
    u8 pad_00[8];
    u32 *base;
    u32 *start;
    u32 *cursor;
    u8 *end;
    ScriptSlot slots[11];
} ScriptFrame;

typedef struct ScriptExtra {
    u8 pad_00[0xc];
    s32 unk_0C;
    u8 pad_10[0x40];
    s32 unk_50;
} ScriptExtra;

typedef struct ScriptVm {
    s32 stackUsed;
    ScriptFrame frames[4];
    s32 depth;
    ScriptExtra *extra;
    u8 pad_1cc[0x624 - 0x1cc];
    u8 *skipTarget;
    s32 skipRequested;
    s32 skipping;
    s32 unk_630;
    u8 pad_634[8];
    u32 *scriptData;
} ScriptVm;

extern void func_0202d314(void *archive, int extra);
extern int FindNameIndexInTable_02025674(u32 *objectBase, const char *name);
extern u32 *func_0202d3e0(u32 *objectBase, int recordIndex, int entryIndex);
extern void func_01ff8830(void *dst, int value, int size);
extern void SetLoaderCallbacks_02025914(ScriptVm *vm, int writeHandler, int readHandler);

BOOL ScriptVm_Start_0202580c(ScriptVm *vm, const char *entryName, ScriptExtra *extra) {
    u32 *data = vm->scriptData;
    int index = 0;

    vm->depth = 0;
    vm->skipTarget = NULL;
    vm->skipRequested = 0;
    vm->skipping = 0;
    vm->unk_630 = 0;

    if (*data == 0x504b4143) {
        func_0202d314(data, 0);
        if (entryName != NULL) {
            index = FindNameIndexInTable_02025674(data, entryName);
        }
        data = func_0202d3e0(data, 1, index);
        vm->frames[0].base = data;
        vm->frames[0].start = data + 1;
        vm->frames[0].cursor = data + 1;
        vm->frames[0].end = (u8 *)data + *data;
    } else {
        vm->frames[0].base = data;
        vm->frames[0].start = data + 1;
        vm->frames[0].cursor = data + 1;
        vm->frames[0].end = (u8 *)data + *data;
    }
    vm->frames[0].slots[0].fn = NULL;
    vm->frames[0].slots[0].arg = 0;
    func_01ff8830((u8 *)vm->frames + 0x20, 0, sizeof(ScriptSlot) * 10);
    extra->unk_0C = 0x10;
    extra->unk_50 = 0;
    vm->extra = extra;
    SetLoaderCallbacks_02025914(vm, 0, 0);
    return TRUE;
}
