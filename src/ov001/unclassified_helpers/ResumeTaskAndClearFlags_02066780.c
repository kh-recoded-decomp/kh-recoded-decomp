#include "nitro/types.h"

typedef struct TaskHost {
    u8 pad_00[0x3c];
    u8 task[0x10];
    void *activeList;
    u8 pad_50[0x1bf];
    u8 suspended : 1;
    u8 suspendPending : 1;
} TaskHost;

extern TaskHost *data_ov001_020a0464;
extern void func_02036710(void *task);

void ResumeTaskAndClearFlags_02066780(void) {
    if (data_ov001_020a0464->activeList != NULL) {
        func_02036710(data_ov001_020a0464->task);
    }
    data_ov001_020a0464->suspended = 0;
    data_ov001_020a0464->suspendPending = 0;
}
