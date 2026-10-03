#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
    u32 *resource;
} TaskDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
} TaskOwner;

typedef struct {
    int resourceId;
    u32 animationName;
    s32 slotCount;
    u32 modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    void (*cleanup)();
    void (*update)();
    u8 pad_2c[4];
    void (*onEvent)();
    u8 pad_34[4];
    void (*onStart)();
    void (*onAction)();
    u32 resourceId;
    u8 pad_44[0xc];
    u16 groupA;
    u16 groupB;
    void *messages;
    void *model;
    void *cameraPath;
} SceneTask;

extern char data_ov063_020d8700[];
extern char data_ov063_020d8708[];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void CameraPath_Load_020c2ec0(void *path, const char *name);
extern void InitScriptTask_020adc5c(SceneTask *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern int func_ov021_020a89a8(EntryGroupDesc *desc);
extern void InitObjWithCallback_020aaf8c(void *obj, u32 player, u32 arg);
extern void func_ov063_020d81a4(TaskOwner *owner, SceneTask *task);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle_020adaf0(TaskOwner *owner, void *resDesc, u32 id, u32 key);
extern void LoadResGroupHandles_020adc14(SceneTask *task, TaskOwner *owner, void *resDesc);
extern void func_ov063_020d818c();
extern void BeginBossIntroScene_020d8100();
extern void func_ov063_020d815c();
extern void func_ov063_020d8180();
extern void func_ov063_020d8198();
extern void func_ov063_020d8298();

SceneTask *CreateSceneTask_020d859c(TaskOwner *owner, void *resDesc, TaskDesc *desc)
{
    SceneTask *task = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(SceneTask));
    EntryGroupDesc group;
    u32 high;
    void *messages;
    u32 base;

    task->cameraPath = NNSi_FndAllocFromDefaultHeap_0202a178(0x60);
    CameraPath_Load_020c2ec0(task->cameraPath, data_ov063_020d8700);
    InitScriptTask_020adc5c(task, 4, desc->id, desc->arg);
    task->update = func_ov063_020d818c;
    task->onStart = BeginBossIntroScene_020d8100;
    task->draw = func_ov063_020d815c;
    task->cleanup = func_ov063_020d8180;
    task->onEvent = func_ov063_020d8198;
    task->onAction = func_ov063_020d8298;
    messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov063_020d8708, owner->player + 8, FALSE);
    task->messages = messages;
    ZeroBytes0x14_020a8adc(&group);
    high = (((u32)messages + 0x8000) & 0xfffffc) << 7;
    group.modelName = high | 0x80000000;
    group.animationName = high | 0x80000001;
    group.slotCount = 1;
    task->groupA = func_ov021_020a89a8(&group);
    ZeroBytes0x14_020a8adc(&group);
    group.modelName = high | 0x80000002;
    group.animationName = high | 0x80000003;
    group.slotCount = 2;
    task->groupB = func_ov021_020a89a8(&group);
    task->model = NNSi_FndAllocFromDefaultHeap_0202a178(0x3c);
    InitObjWithCallback_020aaf8c(task->model, owner->player, 1);
    func_ov063_020d81a4(owner, task);
    task->resourceId = *desc->resource;
    task->handleCount = 1;
    task->handles = NNSi_FndAllocFromDefaultHeap_0202a178(task->handleCount * 4);
    base = func_ov001_0206dba0(4);
    task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, task->resourceId,
        ((((base + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (task->resourceId & 0x1ff));
    LoadResGroupHandles_020adc14(task, owner, resDesc);
    return task;
}
