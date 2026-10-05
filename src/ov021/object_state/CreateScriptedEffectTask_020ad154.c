#include "nitro/types.h"

typedef struct TaskDesc {
    s16 id;
    u8 pad02[2];
    void *arg;
    void *def;
} TaskDesc;

typedef struct TaskOwner {
    u8 pad00[0x14];
    u32 player;
} TaskOwner;

typedef struct TargetSet {
    int count;
    int *targets;
} TargetSet;

typedef struct ScriptedTask {
    u8 pad00[0x20];
    void *draw;
    void *cleanup;
    void *onHit;
    void *onPause;
    void *onStop;
    u8 pad34[4];
    void *onResume;
    void *onEvent;
    TargetSet targetSet;
    u8 pad48[0x38];
    s8 activeA;
    s8 activeB;
    u8 pad82[2];
    void *extra;
    u8 pad88[0x78];
    int scale;
    u8 pad104[4];
    int timer;
} ScriptedTask;

extern const char data_ov021_020b5274[];
extern const char *data_0205615c[];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void ResetTargetSet_020adf90(TargetSet *set);
extern void InitScriptTask_020adc5c(ScriptedTask *task, int script, int id, void *arg);
extern void SetupEffectSlots_020ad384(ScriptedTask *task, TaskOwner *owner, void *def, void *context);
extern u8 *func_0204f768(u32 player);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *func_0202c48c(const char *path, u32 heapId);
extern void BuildNodeRecords_020ade6c(ScriptedTask *task, TaskOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles_020adf14(ScriptedTask *task, TaskOwner *owner, void *resDesc);
extern void LoadResGroupHandles_020adc14(ScriptedTask *task, TaskOwner *owner, void *resDesc);
extern void InitObjWithCallback_020aaf8c(void *obj, u32 player, u32 mode);
extern void func_ov056_020d3f70(TaskOwner *owner, ScriptedTask *task);
extern void func_ov056_020d3d08(TaskOwner *owner, ScriptedTask *task);
extern void func_ov021_020add78(void);
extern void func_ov021_020ade38(void);
extern void func_ov021_020addcc(void);
extern void func_ov056_020d33f8(void);
extern void func_ov030_020bc4a8(void);
extern void func_ov056_020d3530(void);
extern void func_ov056_020d36dc(void);
extern void func_ov056_020d3904(void);
extern void func_ov056_020d3b1c(void);
extern void func_ov021_020ad470(void);
extern void func_ov021_020ad494(void);
extern void func_ov056_020d3dc8(void);
extern void func_ov056_020d3f1c(void);
extern void func_ov056_020d402c(void);
extern void func_ov056_020d3b30(void);
extern void func_ov021_020adfb8(void);
extern void func_ov056_020d3b24(void);
extern void func_ov056_020d3b40(void);
extern void func_ov056_020d40e0(void);
extern void func_ov021_020ad4a4(void);
extern void UpdateTimedMarkerAction_020d42b4(void);

ScriptedTask *CreateScriptedEffectTask_020ad154(TaskOwner *owner, void *resDesc, TaskDesc *desc, void *context)
{
    ScriptedTask *task;
    TargetSet *targetSet;
    void *file;
    u32 size;
    u32 selection;
    char path[0x80];

    size = 0x84;
    switch (desc->id) {
    case 0x8e:
        size = 0x10c;
        break;
    case 0x8f:
    case 0x90:
        size = 0x88;
        break;
    }
    task = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    func_01ff8830(task, 0, 0x84);
    ResetTargetSet_020adf90(&task->targetSet);
    task->activeA = -1;
    task->activeB = -1;
    InitScriptTask_020adc5c(task, 3, desc->id, desc->arg);
    targetSet = &task->targetSet;
    if (desc->id == 0x8c) {
        targetSet->count = 3;
        targetSet->targets = NNSi_FndAllocFromDefaultHeap_0202a178(targetSet->count * sizeof(int));
        SetupEffectSlots_020ad384(task, owner, desc->def, context);
        targetSet->targets[1] = targetSet->targets[0] + 1;
        targetSet->targets[2] = targetSet->targets[0] + 2;
    } else {
        targetSet->count = 1;
        targetSet->targets = NNSi_FndAllocFromDefaultHeap_0202a178(targetSet->count * sizeof(int));
        SetupEffectSlots_020ad384(task, owner, desc->def, context);
    }
    task->onResume = func_ov021_020add78;
    task->draw = func_ov021_020ade38;
    task->onPause = func_ov021_020addcc;
    task->onEvent = func_ov056_020d33f8;
    selection = *func_0204f768(owner->player);
    OS_SPrintf_02002428(path, data_ov021_020b5274, data_0205615c[selection]);
    file = func_0202c48c(path, 0x11);
    BuildNodeRecords_020ade6c(task, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    AcquireEntryHandles_020adf14(task, owner, resDesc);
    LoadResGroupHandles_020adc14(task, owner, resDesc);
    switch (desc->id) {
    case 0xdc:
        task->onResume = func_ov030_020bc4a8;
        break;
    case 0x8d:
        task->onEvent = func_ov056_020d3530;
        task->onPause = NULL;
        break;
    case 0x8b:
        task->onEvent = func_ov056_020d36dc;
        task->onPause = NULL;
        break;
    case 0x8e:
        task->scale = 0x1000;
        task->timer = 0;
        task->onEvent = func_ov056_020d3904;
        task->cleanup = func_ov056_020d3b1c;
        task->onPause = func_ov021_020ad470;
        task->onStop = func_ov021_020ad494;
        break;
    case 0x8f:
    case 0x90:
        task->extra = NNSi_FndAllocFromDefaultHeap_0202a178(0x3c);
        InitObjWithCallback_020aaf8c(task->extra, owner->player, 1);
        switch (desc->id) {
        case 0x90:
            func_ov056_020d3d08(owner, task);
            task->onEvent = func_ov056_020d3dc8;
            task->cleanup = func_ov056_020d3f1c;
            break;
        case 0x8f:
            func_ov056_020d3f70(owner, task);
            task->onEvent = func_ov056_020d402c;
            task->cleanup = func_ov056_020d3b30;
            break;
        }
        task->draw = func_ov021_020adfb8;
        task->onHit = func_ov056_020d3b24;
        task->onStop = func_ov056_020d3b40;
        break;
    case 0x8c:
        task->onEvent = func_ov056_020d40e0;
        task->onResume = func_ov021_020ad4a4;
        task->onPause = NULL;
        break;
    case 0xf5:
    case 0xf7:
        task->onEvent = UpdateTimedMarkerAction_020d42b4;
        break;
    }
    return task;
}
