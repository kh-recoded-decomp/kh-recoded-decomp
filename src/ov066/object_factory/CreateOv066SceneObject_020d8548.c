#include "nitro/types.h"

typedef struct EntryGroupDesc {
    int kind;
    u32 endKey;
    int param;
    u32 startKey;
    int extra;
} EntryGroupDesc;

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
    u32 *target;
} ObjectDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
} ObjectOwner;

typedef struct {
    s32 count;
    u32 *ids;
    s16 groups[3];
    u8 pad_0e[0x0e];
    s32 scale;
    u8 pad_20[4];
    s32 field24;
    s32 field28;
    u8 pad_2c[8];
} TargetSet;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    u8 pad_24[0x14];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    s16 *groupA;
    s16 *groupB;
    s16 *groupC;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    void *messages;
    void *cameraPath;
} SceneObject;

extern char data_ov066_020d8760[];
extern char data_ov066_020d8768[];
extern char data_ov066_020d8778[];
extern char *data_0205615c[];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void CameraPath_Load_020c2ec0(void *path, const char *name);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void InitScriptTask_020adc5c(SceneObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet_020adf90(TargetSet *set);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern s16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern u8 *func_0204f768(u32 player);
extern void OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *func_0202c48c(const char *name, u32 mode);
extern void BuildNodeRecords_020ade6c(SceneObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle_020adaf0(ObjectOwner *owner, void *resDesc, int id, u32 key);
extern void LoadResGroupHandles_020adc14(SceneObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov066_020d8100();
extern void func_ov066_020d81c8();
extern void func_ov066_020d81f4();

SceneObject *CreateOv066SceneObject_020d8548(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    SceneObject *obj = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(SceneObject));
    u32 targetId;
    TargetSet *targets;
    EntryGroupDesc group;
    void *file;
    u32 base;
    u32 selection;
    char path[128];

    obj->cameraPath = NNSi_FndAllocFromDefaultHeap_0202a178(0x60);
    CameraPath_Load_020c2ec0(obj->cameraPath, data_ov066_020d8760);
    func_01ff8830(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask_020adc5c(obj, 4, desc->id, desc->arg);
    obj->messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov066_020d8768, owner->player + 8, FALSE);
    targets = &obj->targets;
    targetId = *desc->target;
    ResetTargetSet_020adf90(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap_0202a178(obj->targets.count * 4);
    targets->ids[0] = 0x16440;
    targets->field28 = 0;
    targets->field24 = 0;
    targets->scale = 0x1000;
    ZeroBytes0x14_020a8adc(&group);
    group.startKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000000;
    group.endKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000001;
    group.param = 1;
    targets->groups[0] = func_ov021_020a89a8(&group);
    obj->groupA = &targets->groups[0];
    ZeroBytes0x14_020a8adc(&group);
    group.startKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000002;
    group.endKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000003;
    group.param = 1;
    targets->groups[1] = func_ov021_020a89a8(&group);
    obj->groupB = &targets->groups[1];
    ZeroBytes0x14_020a8adc(&group);
    group.startKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000004;
    group.endKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000005;
    group.param = 1;
    targets->groups[2] = func_ov021_020a89a8(&group);
    obj->groupC = &targets->groups[2];
    obj->onStart = func_ov066_020d8100;
    obj->draw = func_ov066_020d81c8;
    obj->onAction = func_ov066_020d81f4;

    selection = *func_0204f768(owner->player);
    OS_SPrintf_02002428(path, data_ov066_020d8778, data_0205615c[selection]);
    file = func_0202c48c(path, 0x11);
    BuildNodeRecords_020ade6c(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    obj->handleCount = 1;
    obj->handles = NNSi_FndAllocFromDefaultHeap_0202a178(obj->handleCount * 4);
    base = func_ov001_0206dba0(4);
    obj->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, targetId,
        ((base + 0x8000 & 0xfffffc) << 7) | 0x80000000 | (targetId & 0x1ff));
    LoadResGroupHandles_020adc14(obj, owner, resDesc);
    return obj;
}
