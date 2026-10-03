#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EffectDef {
    u8 pad_00[8];
    s32 sizeX;
    s32 sizeY;
    u8 pad_10[8];
    u32 flags;
} EffectDef;

typedef struct EffectDesc {
    s16 id;
    u8 pad_02[2];
    void *arg;
    EffectDef *def;
} EffectDesc;

typedef struct EffectOwner {
    u8 pad_00[0x14];
    u32 player;
} EffectOwner;

typedef struct EffectTask {
    u8 pad_00[8];
    int scriptArg;
    u8 pad_0c[4];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*update)(void);
    void (*draw)(void);
    void (*cleanup)(void);
    u8 pad_2c[0x38 - 0x2c];
    void (*onResume)(void);
    void (*onEvent)(void);
    u32 flags;
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    int page;
} EffectTask;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void InitScriptTask_020adc5c(EffectTask *task, int script, int id, void *arg);
extern int DispatchPageHandler_020d3a94(EffectDef *def, int arg1, int arg2);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle_020adaf0(EffectOwner *owner, void *desc, int id, u32 key);
extern void func_ov055_020d3acc(void);
extern void func_ov021_020adc80(void);
extern void func_ov021_020adc8c(void);
extern void func_ov055_020d3afc(void);
extern void func_ov055_020d3c00(void);

EffectTask *CreatePageEffectTask_020d3ddc(EffectOwner *owner, void *resDesc, EffectDesc *desc)
{
    EffectTask *task = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(EffectTask));
    EffectDef *def;
    u32 base;
    int slot;

    InitScriptTask_020adc5c(task, 2, desc->id, desc->arg);
    task->update = func_ov055_020d3acc;
    task->onResume = func_ov055_020d3afc;
    task->draw = func_ov021_020adc80;
    task->cleanup = func_ov021_020adc8c;
    task->onEvent = func_ov055_020d3c00;
    def = desc->def;
    task->page = DispatchPageHandler_020d3a94(def, task->scriptArg, owner->player);
    task->flags = def->flags;
    task->scaleX = 0x9000;
    task->scaleY = 0xf000;
    if (def->sizeX >= 0) {
        task->scaleX = def->sizeX << 12;
    }
    if (def->sizeY >= 0) {
        task->scaleY = def->sizeY << 12;
    }
    base = func_ov001_0206dba0(5);
    slot = 0;
    if (desc->id != 0xf1) {
        slot = 2;
    }
    task->handleCount = 1;
    task->handles = NNSi_FndAllocFromDefaultHeap_0202a178(task->handleCount * 4);
    switch (slot) {
    case 2:
        task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, 1, 0x80000001 | (((base + 0x8000) & 0xfffffc) << 7));
        break;
    case 0:
        task->handles[0] = AcquireRecordHandle_020adaf0(owner, resDesc, 0, 0x80000000 | (((base + 0x8000) & 0xfffffc) << 7));
        break;
    }
    return task;
}
