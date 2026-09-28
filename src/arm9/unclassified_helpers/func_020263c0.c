#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c4];
    s32 currentIndex;
} ScriptVm;

extern int func_0202c38c(void *addr);
extern void func_0202d314(void *addr, int flag);
extern int func_02025dac(int scriptCtx, unsigned short *operand);
extern int func_0202633c(ScriptVm *vm, void *addr, int value, int result);

int func_020263c0(ScriptVm *vm, u8 *param2)
{
    int bufferBase = *(int *)vm;
    int bufferPos = *(int *)((u8 *)vm + 0x63c);
    int value;
    int result;

    if (func_0202c38c((void *)(bufferPos + bufferBase)) == 0) {
        return 0;
    }
    if (*(int *)(bufferPos + bufferBase) == 0x504b4143) {
        func_0202d314((void *)(bufferPos + bufferBase), 0);
    }
    value = *(int *)((u8 *)vm + (vm->currentIndex + 1) * 0x70 + 8);
    if (*(short *)(param2 + 8) != 0) {
        result = func_02025dac((int)vm, (unsigned short *)(param2 + 8));
    } else {
        result = 0;
    }
    func_0202633c(vm, (void *)(bufferPos + bufferBase), value, result);
    return 2;
}
