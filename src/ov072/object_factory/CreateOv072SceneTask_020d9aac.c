#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
} TaskDesc;

typedef struct {
    int kind;
    u32 firstKey;
    u32 name;
    u32 secondKey;
    int extra;
} EntryGroupDesc;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    void (*cleanup)();
    u8 pad_28[4];
    void (*update)();
    void (*onEvent)();
    u8 pad_34[4];
    void (*onStart)();
    u8 pad_3c[4];
    u16 groups[5];
    u8 pad_4a[2];
    void *cameraPath;
    u8 pad_50[0x28];
    int scale;
    void *messages;
    u8 pad_80[0xc];
} SceneTask;

extern char data_ov072_020d9c00[];
extern char data_ov072_020d9c10[];
extern const u32 data_ov072_020d9bc8[];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void CameraPath_Load_020c2ec0(void *path, const char *name);
extern void InitScriptTask_020adc5c(SceneTask *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern int func_ov021_020a89a8(EntryGroupDesc *desc);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle_020adaf0(void *owner, void *resDesc, u32 id, u32 key);
extern void LoadResGroupHandles_020adc14(SceneTask *task, void *owner, void *resDesc);
extern void InitOv072ActorState_020d8138();
extern void func_ov072_020d82e8();
extern void func_ov072_020d8234();
extern void func_ov072_020d82d8();
extern void func_ov072_020d8230();

SceneTask *CreateOv072SceneTask_020d9aac(void *owner, void *resDesc, TaskDesc *desc)
{
    SceneTask *task = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(SceneTask));
    int i = 0;
    EntryGroupDesc group;
    void *messages;
    u32 base;
    u32 high;

    InitScriptTask_020adc5c(task, 4, desc->id, desc->arg);
    task->onStart = InitOv072ActorState_020d8138;
    task->draw = func_ov072_020d82e8;
    task->update = func_ov072_020d8234;
    task->onEvent = func_ov072_020d82d8;
    task->cleanup = func_ov072_020d8230;
    base = func_ov001_0206dba0(4);
    task->handleCount = 1;
    task->handles = NNSi_FndAllocFromDefaultHeap_0202a178(task->handleCount * 4);
    task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, 11,
        ((((base + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (11 & 0x1ff));
    LoadResGroupHandles_020adc14(task, owner, resDesc);
    messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov072_020d9c00, 0x11, FALSE);
    ZeroBytes0x14_020a8adc(&group);
    high = ((((u32)messages + 0x8000) & 0xfffffc) << 7) | 0x80000000;
    do {
        group.firstKey = ((i * 2) & 0x1ff) | high;
        group.secondKey = ((i * 2 + 1) & 0x1ff) | high;
        group.name = data_ov072_020d9bc8[i];
        task->groups[i] = func_ov021_020a89a8(&group);
        i++;
    } while (i < 5);
    task->messages = messages;
    task->scale = 0x1000;
    task->cameraPath = NNSi_FndAllocFromDefaultHeap_0202a178(0x60);
    CameraPath_Load_020c2ec0(task->cameraPath, data_ov072_020d9c10);
    return task;
}
