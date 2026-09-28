#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    void *currentThread;
} ThreadInfo_02056b50;

extern ThreadInfo_02056b50 data_02056b50;
extern int func_02004938(void);
extern void func_020029a8(void *thread, int arg1);

void ExitCurrentThread_02002988(void)
{
    func_02004938();
    func_020029a8(data_02056b50.currentThread, 0);
}
