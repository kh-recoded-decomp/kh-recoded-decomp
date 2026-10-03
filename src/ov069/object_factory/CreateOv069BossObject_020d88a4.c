#include "nitro/types.h"

typedef struct EntryGroupDesc {
    int kind;
    u32 endKey;
    int param;
    u32 startKey;
    int extra;
} EntryGroupDesc;

typedef struct {
    s32 mode : 8;
    s32 step : 8;
    s32 count : 16;
} IntroCounter;

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
} ObjectDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
} ObjectOwner;

typedef struct {
    s32 count;
    u32 *ids;
    s16 groupA;
    s16 pad_0a;
    s16 groupB;
    s16 pad_0e;
    s32 field10;
    u8 pad_14[8];
    s32 scale;
    s32 range;
    s32 field24;
    s32 field28;
    u8 pad_2c[8];
} TargetSet;

typedef struct {
    u8 pad_00[0x20];
    void (*draw)();
    u8 pad_24[8];
    void (*finish)();
    u8 pad_30[8];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    s16 *groupAPtr;
    u8 pad_78[4];
    s16 *groupBPtr;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    u8 cameraPath[0x6c];
    int speed;
    void *messages;
    int seqHandle;
    IntroCounter counter;
} BossObject;

extern char data_ov069_020d8a20[];
extern char data_ov069_020d8a30[];
extern char data_ov069_020d8a40[];
extern char *data_0205615c[];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void CameraPath_Load_020c2ec0(void *path, const char *name);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void InitScriptTask_020adc5c(BossObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet_020adf90(TargetSet *set);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern s16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern u8 *func_0204f768(u32 player);
extern void OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *func_0202c48c(const char *name, u32 mode);
extern void BuildNodeRecords_020ade6c(BossObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles_020adf14(BossObject *obj, ObjectOwner *owner, void *resDesc);
extern void LoadManagerSpriteSlots_0206dbb4(void);
extern void LoadResGroupHandles_020adc14(BossObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov069_020d8100();
extern void func_ov069_020d8120();
extern void func_ov069_020d827c();
extern void func_ov069_020d8824();

BossObject *CreateOv069BossObject_020d88a4(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    BossObject *obj = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(BossObject));
    TargetSet *targets;
    u32 key;
    EntryGroupDesc group;
    void *file;
    u32 selection;
    char path[128];

    func_01ff8830(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask_020adc5c(obj, 4, desc->id, desc->arg);
    targets = &obj->targets;
    ResetTargetSet_020adf90(targets);
    obj->targets.count = 2;
    targets->ids = NNSi_FndAllocFromDefaultHeap_0202a178(obj->targets.count * 4);
    targets->ids[0] = 0x33f4;
    targets->ids[1] = 0x3458;
    obj->messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov069_020d8a20, owner->player + 8, FALSE);
    key = (u32)obj->messages;
    ZeroBytes0x14_020a8adc(&group);
    key = (key + 0x8000 & 0xfffffc) << 7;
    group.startKey = key | 0x80000000;
    group.endKey = key | 0x80000001;
    group.param = 4;
    targets->groupB = func_ov021_020a89a8(&group);
    obj->onStart = func_ov069_020d8120;
    obj->draw = func_ov069_020d8100;
    obj->finish = func_ov069_020d8824;
    obj->onAction = func_ov069_020d827c;
    selection = *func_0204f768(owner->player);
    OS_SPrintf_02002428(path, data_ov069_020d8a30, data_0205615c[selection]);
    file = func_0202c48c(path, 0x11);
    BuildNodeRecords_020ade6c(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    AcquireEntryHandles_020adf14(obj, owner, resDesc);
    LoadResGroupHandles_020adc14(obj, owner, resDesc);
    obj->counter.mode = 0;
    obj->counter.step = 0;
    obj->counter.count = 0;
    LoadManagerSpriteSlots_0206dbb4();
    CameraPath_Load_020c2ec0(obj->cameraPath, data_ov069_020d8a40);
    return obj;
}
