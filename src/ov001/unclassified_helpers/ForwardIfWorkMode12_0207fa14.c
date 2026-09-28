#include "nitro/types.h"

typedef struct FieldWork {
    u8 pad_00[0x7D];
    u8 mode;
} FieldWork;

typedef struct FieldTask {
    u8 pad_00[0x8];
    FieldWork *work;
} FieldTask;

extern int func_ov008_020a0c28(FieldTask *task, int arg1, int arg2);

int ForwardIfWorkMode12_0207fa14(FieldTask *task, int arg1, int arg2)
{
    if (task->work->mode == 12) {
        return func_ov008_020a0c28(task, arg1, arg2);
    }
    return 0;
}
