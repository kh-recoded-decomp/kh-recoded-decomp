#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x3d];
    s8 kind;
} EffectSource;

typedef struct {
    u8 pad_00[8];
    s32 sizeX;
    s32 sizeY;
    s32 sizeZ;
    u8 pad_14[4];
    u32 flags;
} EffectDef;

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
    EffectDef *def;
} EffectDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
} EffectOwner;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*update)(void);
    void (*draw)(void);
    void (*cleanup)(void);
    u8 pad_2c[4];
    void (*onPause)(void);
    u8 pad_34[4];
    void (*onResume)(void);
    void (*onEvent)(void);
    u32 flags;
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    EffectSource *source;
} EffectTask;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void InitScriptTask_020adc5c(EffectTask *task, int script, int id, void *arg);
extern EffectSource *func_ov056_020d7d84(EffectDef *def, void *arg, u32 player);
extern u32 func_ov001_0206dba0(int index);
extern int MapKindToSlot_020d7cc4(int kind);
extern void *AcquireRecordHandle_020adaf0(EffectOwner *owner, void *desc, int id, u32 key);
extern void LoadResGroupHandles_020adc14(EffectTask *task, EffectOwner *owner, void *desc);
extern void func_ov021_020ad044(void);
extern void func_ov021_020adc80(void);
extern void func_ov021_020adc8c(void);
extern void func_ov021_020ad064(void);
extern void func_ov021_020ad058(void);
extern void func_ov056_020d316c(void);

EffectTask *CreateEffectTask_020acedc(EffectOwner *owner, void *resDesc, EffectDesc *desc)
{
    EffectTask *task = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(EffectTask));
    EffectDef *def;
    u32 base;
    int slot;

    InitScriptTask_020adc5c(task, 2, desc->id, desc->arg);
    task->update = func_ov021_020ad044;
    task->draw = func_ov021_020adc80;
    task->cleanup = func_ov021_020adc8c;
    task->onResume = func_ov021_020ad064;
    task->onPause = func_ov021_020ad058;
    task->onEvent = func_ov056_020d316c;
    def = desc->def;
    task->source = func_ov056_020d7d84(def, desc->arg, owner->player);
    task->flags = def->flags;
    task->scaleX = 0x9000;
    task->scaleY = 0xf000;
    task->scaleZ = 0;
    if (def->sizeX >= 0) {
        task->scaleX = def->sizeX << 12;
    }
    if (def->sizeY >= 0) {
        task->scaleY = def->sizeY << 12;
    }
    if (def->sizeZ >= 0) {
        task->scaleZ = def->sizeZ << 12;
    }
    base = func_ov001_0206dba0(4);
    slot = MapKindToSlot_020d7cc4(task->source->kind);
    task->handleCount = 1;
    if (slot == 0) {
        task->handleCount = 2;
    }
    task->handles = NNSi_FndAllocFromDefaultHeap_0202a178(task->handleCount * 4);
    switch (slot) {
    case 2:
        task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, 3, 0x80000003 | (((base + 0x8000) & 0xfffffc) << 7));
        break;
    case 0: {
        u32 vram = ((base + 0x8000) & 0xfffffc) << 7;
        task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, 1, vram | 0x80000001);
        task->handles[1] = AcquireRecordHandle_020adaf0(owner, resDesc, 2, vram | 0x80000002);
        break;
    }
    case 4:
    case 5:
    case 6:
    case 7:
    case 8: {
        int layer = slot - 4;
        task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, layer + 4, 0x80000000 | (((base + 0x8000) & 0xfffffc) << 7) | ((layer + 4) & 0x1ff));
        break;
    }
    }
    LoadResGroupHandles_020adc14(task, owner, resDesc);
    return task;
}
