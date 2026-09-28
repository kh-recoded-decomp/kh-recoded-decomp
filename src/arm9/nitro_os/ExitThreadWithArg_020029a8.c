#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *stackForDestructor;
} ThreadInfo_02056b50;

extern ThreadInfo_02056b50 data_02056b50;
extern void func_02002ddc(void *thread, void *newpc, void *newsp);
extern void func_02002a00(void *arg);
extern void func_02002e94(void *thread);

void ExitThreadWithArg_020029a8(void *thread, void *arg)
{
    if (data_02056b50.stackForDestructor != NULL) {
        func_02002ddc(thread, (void *)func_02002a00, data_02056b50.stackForDestructor);
        *(u32 *)thread = *(u32 *)thread | 0x80;
        *(void **)((u8 *)thread + 4) = arg;
        *(u32 *)((u8 *)thread + 0x64) = 1;
        func_02002e94(thread);
        return;
    }
    func_02002a00(arg);
}
