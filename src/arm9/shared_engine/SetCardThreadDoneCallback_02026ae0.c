#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void (*doneCallback)(void);
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void func_02027110(void);

void SetCardThreadDoneCallback_02026ae0(void)
{
    g_cardThreadState_0205fe00.doneCallback = func_02027110;
}
