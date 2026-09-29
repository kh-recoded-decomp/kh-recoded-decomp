#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x64];
    u32 state;
} OSThread;

typedef void (*OSSwitchThreadCallback)(OSThread *from, OSThread *to);

typedef struct OSThreadInfo {
    OSSwitchThreadCallback systemCallback;
    u32 rescheduleCount;
    OSThread **currentThreadPtr;
    u8 pad_0C[0x12];
    u16 irqDepth;
    OSThread *currentThread;
} OSThreadInfo;

typedef struct OSRescheduleState {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *currentThread;
    OSThread *list;
    OSSwitchThreadCallback switchCallback;
} OSRescheduleState;

extern OSThreadInfo data_02056b50;
extern OSRescheduleState data_02056b6c;

extern int func_0200499c(void);
extern OSThread *SelectReadyThread_02002b88(void);
extern BOOL func_02002e48(OSThread *thread);
extern void func_02002e94(OSThread *thread);

void OSi_RescheduleThread_02002688(void)
{
    OSRescheduleState *state;
    OSThread **currentPtr;
    OSThread *current;
    OSThread *next;
    OSSwitchThreadCallback callback;

    if (data_02056b50.rescheduleCount != 0) {
        return;
    }

    state = &data_02056b6c;
    if (data_02056b50.irqDepth != 0 || func_0200499c() == 0x12) {
        state->isNeedRescheduling = 1;
        return;
    }

    currentPtr = data_02056b50.currentThreadPtr;
    current = *currentPtr;
    next = SelectReadyThread_02002b88();

    if (current == next || next == NULL) {
        return;
    }

    if (current->state != 2) {
        if (func_02002e48(current)) {
            return;
        }
    }

    callback = data_02056b50.systemCallback;
    if (callback != NULL) {
        callback(current, next);
    }

    callback = state->switchCallback;
    if (callback != NULL) {
        callback(current, next);
    }

    data_02056b50.currentThread = next;
    func_02002e94(next);
}
