#include "nitro/types.h"

typedef struct {
    u32 debuggerHandler;
    u32 pad_04;
    u32 savedVector;
    void *userHandler;
} OSiExceptionState;

extern OSiExceptionState data_02056df0;
extern void func_02003d20(void);

void OS_InitException_02003ca8(void)
{
    BOOL isDebuggerVector = FALSE;
    u32 *vectorSlot = (u32 *)0x02fffd9c;
    u32 vector = *vectorSlot;

    data_02056df0.savedVector = vector;
    if (vector >= 0x02600000 && vector < 0x02800000) {
        isDebuggerVector = TRUE;
    }
    if (!isDebuggerVector) {
        vector = 0;
    }
    data_02056df0.debuggerHandler = vector;

    if (vector == 0) {
        *vectorSlot = (u32)func_02003d20;
        *(u32 *)((u32)vectorSlot & ~0x00800000) = (u32)func_02003d20;
    }
    data_02056df0.userHandler = NULL;
}
