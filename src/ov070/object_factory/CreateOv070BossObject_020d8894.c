#include "nitro/types.h"
#include "nitro/fx_types.h"

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
} ObjectDesc;

typedef struct {
    u32 values[3];
} GroupTable;

typedef struct {
    int active;
    int timer;
    int handle;
    u8 pad_0c[0xc];
    VecFx32 pos;
} EffectSlot;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    void (*cleanup)();
    u8 pad_28[4];
    void (*finish)();
    void (*update)();
    u8 pad_34[4];
    void (*onStart)();
    u8 pad_3c[4];
    u8 running;
    u8 pad_41[3];
    int field44;
    int field48;
    u8 pad_4c[4];
    s16 groups[3];
    u8 pad_56[2];
    int loopHandle;
    u8 pad_5c[4];
    EffectSlot slots[10];
    void *messages;
} BossObject;

extern const GroupTable data_ov070_020d8a04;
extern const GroupTable data_ov070_020d8a10;
extern char data_ov070_020d8a40[];
extern const VecFx32 data_02053438;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void InitScriptTask_020adc5c(BossObject *task, int script, int id, void *arg);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle_020adaf0(void *owner, void *resDesc, int id, u32 key);
extern void LoadResGroupHandles_020adc14(BossObject *obj, void *owner, void *resDesc);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern s16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern void StartOv070BossTurn_020d8138();
extern void func_ov070_020d828c();
extern void StopOv070BossEffects_020d8210();
extern void func_ov070_020d827c();
extern void func_ov070_020d829c();

BossObject *CreateOv070BossObject_020d8894(void *owner, void *resDesc, ObjectDesc *desc)
{
    BossObject *obj = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(BossObject));
    int i;
    void *messages;
    EntryGroupDesc group;
    GroupTable params;
    GroupTable indices;
    VecFx32 zero;
    u32 key;
    EffectSlot *slot;

    InitScriptTask_020adc5c(obj, 4, desc->id, desc->arg);
    obj->onStart = StartOv070BossTurn_020d8138;
    obj->draw = func_ov070_020d828c;
    obj->finish = StopOv070BossEffects_020d8210;
    obj->update = func_ov070_020d827c;
    obj->cleanup = func_ov070_020d829c;
    obj->running = 0;
    obj->field44 = 0;
    obj->field48 = 0;
    obj->loopHandle = -1;
    obj->handleCount = 1;
    obj->handles = NNSi_FndAllocFromDefaultHeap_0202a178(obj->handleCount * 4);
    obj->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, 9,
        ((func_ov001_0206dba0(4) + 0x8000 & 0xfffffc) << 7) | 0x80000000 | 9);
    LoadResGroupHandles_020adc14(obj, owner, resDesc);
    params = data_ov070_020d8a04;
    indices = data_ov070_020d8a10;
    messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov070_020d8a40, 0x11, FALSE);
    ZeroBytes0x14_020a8adc(&group);
    key = (((u32)messages + 0x8000 & 0xfffffc) << 7) | 0x80000000;
    i = 0;
    do {
        group.endKey = (indices.values[i] & 0x1ff) | key;
        group.startKey = (indices.values[i] + 1 & 0x1ff) | key;
        group.param = params.values[i];
        obj->groups[i] = func_ov021_020a89a8(&group);
        i++;
    } while (i < 3);
    obj->messages = messages;
    i = 0;
    zero = data_02053438;
    for (; i < 10; i++) {
        slot = &obj->slots[i];
        slot->active = 0;
        slot->timer = 0;
        slot->pos = zero;
        *(VecFx32 *)&slot->pos = zero;
    }
    return obj;
}
