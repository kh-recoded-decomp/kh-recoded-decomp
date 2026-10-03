#include "nitro/types.h"

typedef struct {
    void *owner;
    void *script;
    void *arg;
    u8 pad_0C[0x28];
    void (*update)(void *task);
    u8 pad_38[8];
} ScriptTask;

extern void MIi_CpuFill8_01ff8830(void *dest, u8 data, u32 size);
extern void func_ov021_020acdb4(void *task);

void InitScriptTask_020adc5c(ScriptTask *task, void *script, void *owner, void *arg) {
    MIi_CpuFill8_01ff8830(task, 0, sizeof(ScriptTask));
    task->script = script;
    task->owner = owner;
    task->arg = arg;
    task->update = func_ov021_020acdb4;
}
