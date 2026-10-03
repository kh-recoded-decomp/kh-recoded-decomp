#include "nitro/types.h"

typedef struct {
    s16 id;
    u16 pad;
    void *arg;
    u32 *res;
} TaskDesc;

typedef struct {
    void *owner;
    void *script;
    void *arg;
    u32 pad_0C;
    u32 **layers;
    int layerCount;
    u32 *extras;
    int extraCount;
    u8 pad_20[0x18];
    void (*update)(void *task);
    void (*draw)(void *task);
    u16 handle;
    u16 pad_42;
} LayerTask;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void InitScriptTask_020adc5c(void *task, void *script, void *owner, void *arg);
extern u16 func_ov021_020acc00(void *ctx, u32 res, int a, int b);
extern unsigned int func_ov001_0206e62c(void);
extern u32 func_ov001_0206dba0(u32 index);
extern u32 *func_ov021_020adaf0(void *ctx, void *arg, int mode, u32 attr);
extern u32 func_ov021_020adb44(void *ctx, void *arg, u32 value, int mode);
extern void func_ov021_020ace8c(void *task);
extern void func_020d0748(void *task);

LayerTask *CreateLayerTask_020acdc0(void *ctx, void *arg, TaskDesc *desc) {
    LayerTask *task = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(LayerTask));
    int count = 1;
    u32 attr;
    int bank;
    InitScriptTask_020adc5c(task, (void *)1, (void *)(int)desc->id, desc->arg);
    task->update = func_ov021_020ace8c;
    task->draw = func_020d0748;
    task->handle = func_ov021_020acc00(ctx, *desc->res, 1, 1);
    if (func_ov001_0206e62c() == 0) {
        count = 2;
    }
    task->layerCount = count;
    task->layers = NNSi_FndAllocFromDefaultHeap_0202a178(count << 2);
    bank = 4;
    attr = ((func_ov001_0206dba0(bank) + (bank << 13)) & 0xfffffc) << 7;
    task->layers[task->layerCount - 1] = func_ov021_020adaf0(ctx, arg, 14, attr | 0x8000000e);
    if (count > 1) {
        task->layers[0] = func_ov021_020adaf0(ctx, arg, 0, attr | 0x80000000);
        task->extraCount = 1;
        task->extras = NNSi_FndAllocFromDefaultHeap_0202a178(task->extraCount << 2);
        task->extras[0] = func_ov021_020adb44(ctx, arg, task->layers[0][1], 0);
    }
    return task;
}
