#include "nitro/types.h"

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
    u16 groupA;
    u8 pad_0a[2];
    u16 groupB;
    u8 pad_0e[0xe];
    s32 scale;
    s32 limit;
    s32 field24;
    s32 field28;
    u8 pad_2c[8];
} TargetSet;

typedef struct {
    int resourceId;
    u32 animationName;
    s32 slotCount;
    u32 modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u8 pad_00[0x20];
    void (*draw)();
    void (*cleanup)();
    void (*update)();
    void (*onEvent)();
    u8 pad_30[8];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    u16 *groupALink;
    u8 pad_78[4];
    u16 *groupBLink;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    void *messages;
    u8 pad_88[4];
    void *cameraPath;
} BattleObject;

extern char data_ov061_020d8520[];
extern char data_ov061_020d8528[];
extern char data_ov061_020d8538[];
extern char *data_0205615c[];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void CameraPath_Load_020c2ec0(void *path, const char *name);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void InitScriptTask_020adc5c(BattleObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet_020adf90(TargetSet *set);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern int func_ov021_020a89a8(EntryGroupDesc *desc);
extern u8 *func_0204f768(u32 player);
extern void OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *func_0202c48c(const char *name, u32 mode);
extern void BuildNodeRecords_020ade6c(BattleObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles_020adf14(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void LoadResGroupHandles_020adc14(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void BeginGuardIntroScene_020d8100();
extern void func_ov061_020d8194();
extern void func_ov021_020addcc();
extern void UpdateTimedBurstAction_020d81c0();

BattleObject *CreateBurstBattleObject_020d8360(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    BattleObject *obj = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(BattleObject));
    u32 targetId;
    TargetSet *targets;
    void *file;
    u32 selection;
    EntryGroupDesc group;
    char path[128];

    obj->cameraPath = NNSi_FndAllocFromDefaultHeap_0202a178(0x60);
    CameraPath_Load_020c2ec0(obj->cameraPath, data_ov061_020d8520);
    func_01ff8830(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask_020adc5c(obj, 4, desc->id, desc->arg);
    obj->messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov061_020d8528, owner->player + 8, FALSE);
    targets = &obj->targets;
    targetId = *desc->target;
    ResetTargetSet_020adf90(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap_0202a178(obj->targets.count * 4);
    targets->ids[0] = targetId;
    targets->field28 = 0;
    targets->field24 = 0;
    targets->scale = 0x1000;
    ZeroBytes0x14_020a8adc(&group);
    group.modelName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000002;
    group.animationName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000003;
    group.slotCount = 2;
    targets->groupA = func_ov021_020a89a8(&group);
    obj->groupALink = &targets->groupA;
    ZeroBytes0x14_020a8adc(&group);
    group.modelName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000000;
    group.animationName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000001;
    group.slotCount = 2;
    targets->groupB = func_ov021_020a89a8(&group);
    obj->groupBLink = &targets->groupB;
    obj->onStart = BeginGuardIntroScene_020d8100;
    obj->draw = func_ov061_020d8194;
    obj->onEvent = func_ov021_020addcc;
    obj->onAction = UpdateTimedBurstAction_020d81c0;
    selection = *func_0204f768(owner->player);
    OS_SPrintf_02002428(path, data_ov061_020d8538, data_0205615c[selection]);
    file = func_0202c48c(path, 0x11);
    BuildNodeRecords_020ade6c(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    AcquireEntryHandles_020adf14(obj, owner, resDesc);
    LoadResGroupHandles_020adc14(obj, owner, resDesc);
    return obj;
}
