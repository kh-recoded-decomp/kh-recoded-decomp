#include "nitro/types.h"

typedef void (*PoolCallback)(void);

typedef struct GridEntryPool {
    PoolCallback update;
    PoolCallback draw;
    void *field_08;
    PoolCallback onRemove;
    void *field_10;
    void *field_14;
    PoolCallback onInit;
    PoolCallback onEnter;
    void *field_20;
    PoolCallback onLeave;
    void *field_28;
    PoolCallback onQuery;
    u8 pad_30[0x8];
    PoolCallback onReset;
    u8 pad_3c[0x8];
    int selected;
    int active;
    u8 pad_4c[0xe];
    u8 kind;
} GridEntryPool;

extern GridEntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void func_ov017_020a2640(void);
extern void func_ov017_020a274c(void);
extern void func_ov017_020a286c(void);
extern void func_ov017_020a2750(void);
extern void func_ov017_020a2754(void);
extern void func_ov017_020a2868(void);
extern void func_ov017_020a28ac(void);
extern void func_ov017_020a2920(void);

GridEntryPool *CreateGridEntryPool_020a2a40(int count)
{
    GridEntryPool *pool = CreateEntryPool_02086258(0x60, 0x50, count);

    pool->active = 0;
    pool->selected = -1;
    pool->update = func_ov017_020a2640;
    pool->field_08 = NULL;
    pool->field_10 = NULL;
    pool->field_14 = NULL;
    pool->onInit = func_ov017_020a274c;
    pool->onReset = func_ov017_020a286c;
    pool->onEnter = func_ov017_020a2750;
    pool->field_20 = NULL;
    pool->onLeave = func_ov017_020a2754;
    pool->field_28 = NULL;
    pool->onRemove = func_ov017_020a2868;
    pool->draw = func_ov017_020a28ac;
    pool->onQuery = func_ov017_020a2920;
    pool->kind = 8;
    return pool;
}
