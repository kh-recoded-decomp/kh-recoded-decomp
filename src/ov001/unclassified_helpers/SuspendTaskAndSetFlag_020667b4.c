#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *next;
} TaskNode;

typedef struct TaskHost {
    u8 pad_00[0x3c];
    u8 task[0x10];
    TaskNode *activeList;
    u8 pad_50[0x1bf];
    u8 suspended : 1;
    u8 suspendPending : 1;
} TaskHost;

typedef struct Session {
    u8 pad_000[0x20e];
    s16 phase;
} Session;

extern Session *data_ov001_020a0460;
extern TaskHost *data_ov001_020a0464;
extern void func_ov001_0206674c(TaskNode *node);
extern void func_02036748(void *task);

void SuspendTaskAndSetFlag_020667b4(void) {
    if (data_ov001_020a0460->phase == ~2) {
        TaskNode *node = data_ov001_020a0464->activeList;
        while (node != NULL) {
            TaskNode *next = node->next;
            func_ov001_0206674c(node);
            node = next;
        }
    }
    if (data_ov001_020a0464->activeList != NULL) {
        func_02036748(data_ov001_020a0464->task);
    }
    data_ov001_020a0464->suspended = 1;
}
