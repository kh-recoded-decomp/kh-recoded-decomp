#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x68];
    struct OSThread *next;
    u8 pad_6c[4];
    u32 priority;
} OSThread;

typedef struct {
    u8 pad_00[0x24];
    OSThread *threadList;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;
extern OSThread data_02056b7c;
extern int func_02004938(void);
extern void func_0200494c(int state);
extern void InsertThreadByPriority_020025e4(OSThread *thread);
extern void func_02002688(void);

int ReprioritizeSleepingThread_02002bd0(OSThread *target, u32 newPriority)
{
    OSThread *current = data_02056b50.threadList;
    OSThread *previous = 0;
    int state = func_02004938();

    while (current != 0 && current != target) {
        previous = current;
        current = current->next;
    }

    if (current == 0 || current == &data_02056b7c) {
        func_0200494c(state);
        return 0;
    }

    if (current->priority != newPriority) {
        if (previous == 0) {
            data_02056b50.threadList = target->next;
        } else {
            previous->next = target->next;
        }
        target->priority = newPriority;
        InsertThreadByPriority_020025e4(target);
        func_02002688();
    }
    func_0200494c(state);
    return 1;
}
