#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 params[10];
} AreaRecord;

typedef struct {
    s16 id;
    u8 sourceIndex;
    u8 pad_03;
} AreaRecordKey;

typedef struct {
    u8 instanceCount;
    u8 recordCount;
    u8 pad_02[2];
    void *instanceKeys;
    u8 *recordSource;
    AreaRecordKey *recordKeys;
} AreaLayout;

typedef struct {
    u8 pad_00[4];
    AreaLayout *layout;
} AreaResource;

typedef struct {
    u8 instanceCount;
    u8 recordCount;
    u8 pad_02[2];
    u8 *instances;
    AreaRecord *records;
} AreaObjects;

typedef struct {
    u8 pad_00[3];
    s8 bossIndex;
    u8 pad_04[0x20];
    u16 *bossBuffer;
    u16 *groupBuffer;
} GroupTable;

typedef struct {
    u8 pad_00[0x2a];
    u16 cursor;
    u16 levelA;
    u16 levelB;
    u8 pad_30[8];
    AreaResource *resource;
    u8 pad_3c[4];
    GroupTable table;
    u8 pad_6c[0x50];
    AreaObjects objects;
} AreaManager;

typedef struct {
    u8 pad_000[0x13c];
    u16 flags;
    u8 pad_13e[2];
    u32 unk_140;
    u32 unk_144;
    u8 pad_148[4];
    void *handle;
} SceneState;

typedef struct {
    u8 pad_00[2];
    u16 levelB;
    u16 levelA;
} LevelInfo;

typedef struct {
    u8 pad_000[0x1d4];
    LevelInfo *levelInfo;
} FieldEntry;

typedef struct {
    u8 pad_00[0x3e];
    u16 size;
    u8 pad_40[0x1a];
    u8 kind;
} BossInfo;

extern AreaManager *data_ov035_020bc4e0;
extern SceneState *data_ov040_020be260;
extern u8 data_ov040_020be234[];
extern u8 data_ov040_020be240[];
extern u8 data_ov001_0209eb18[];
extern void PushVramState_020365a4(void);
extern int func_ov001_02087248(void);
extern BossInfo *func_ov001_02087214(int index);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern int func_ov001_02068984(void);
extern void *func_0202c48c(void *file, int mode);
extern void func_01ff86fc(u32 value, void *dst, u32 size);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void InitInstanceFromTemplate_020bca70(void *table, void *params, void *key, void *instance);
extern void QueueFieldUpdate_020633a0(int arg);
extern FieldEntry *GetBoundedEntryField_0206db5c(int index);
extern void UpdateRewardMenuHighlights_020bde68(FieldEntry *entry, int arg);
extern void *func_0202a448(void *desc, void *arg);
extern LevelInfo *func_0205125c(void);
extern void SetClampedCursor_020a75d8(FieldEntry *entry, u16 value);

static inline void LoadAreaObjects(AreaManager *manager)
{
    int i;
    void *params;
    void *templates;
    AreaObjects *objects = &manager->objects;
    AreaLayout *layout = manager->resource->layout;

    templates = func_0202c48c(data_ov040_020be234, 2);
    params = func_0202c48c(data_ov040_020be240, 2);
    objects->recordCount = layout->recordCount;
    objects->records = NNSi_FndAllocFromDefaultHeap_0202a178(objects->recordCount * sizeof(AreaRecord));
    func_01ff86fc(0, objects->records, objects->recordCount * sizeof(AreaRecord));
    for (i = 0; i < objects->recordCount; i++) {
        objects->records[i].id = layout->recordKeys[i].id;
        func_01ff89a8(layout->recordSource + layout->recordKeys[i].sourceIndex * 12, objects->records[i].params, 9);
    }
    objects->instanceCount = layout->instanceCount;
    objects->instances = NNSi_FndAllocFromDefaultHeap_0202a178(objects->instanceCount * 0x48);
    func_01ff8740(0, objects->instances, objects->instanceCount * 0x48);
    for (i = 0; i < objects->instanceCount; i++) {
        InitInstanceFromTemplate_020bca70(templates, params, (u32 *)layout->instanceKeys + i, objects->instances + i * 0x48);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(templates);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(params);
}

void InitAreaRewardScene_020bd730(BOOL fullInit)
{
    AreaManager *manager = data_ov035_020bc4e0;
    SceneState *scene;
    int i;
    int count;
    GroupTable *table;

    PushVramState_020365a4();
    if (fullInit) {
        table = &data_ov035_020bc4e0->table;
        count = func_ov001_02087248();

        table->bossIndex = -1;
        for (i = 0; i < count; i++) {
            if (func_ov001_02087214(i)->kind == 5) {
                table->bossIndex = i;
            }
        }
        if (table->bossIndex >= 0) {
            table->bossBuffer = NNSi_FndAllocFromDefaultHeap_0202a178(func_ov001_02087214(table->bossIndex)->size * 2);
        } else {
            table->bossBuffer = NULL;
        }
        table->groupBuffer = NNSi_FndAllocFromDefaultHeap_0202a178(func_ov001_02068984() * 2);
        LoadAreaObjects(manager);
    }
    scene = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(SceneState));
    func_01ff86fc(0, scene, sizeof(SceneState));
    scene->unk_140 = 0;
    scene->unk_144 = 0;
    if (fullInit) {
        scene->flags |= 1;
    }
    QueueFieldUpdate_020633a0(0);
    UpdateRewardMenuHighlights_020bde68(GetBoundedEntryField_0206db5c(0), 0);
    scene->handle = func_0202a448(data_ov001_0209eb18, NULL);
    if (fullInit) {
        data_ov035_020bc4e0->levelA = GetBoundedEntryField_0206db5c(0)->levelInfo->levelA;
        data_ov035_020bc4e0->cursor = GetBoundedEntryField_0206db5c(0)->levelInfo->levelB;
        data_ov035_020bc4e0->levelB = func_0205125c()->levelA;
    } else {
        SetClampedCursor_020a75d8(GetBoundedEntryField_0206db5c(0), data_ov035_020bc4e0->cursor);
    }
    data_ov040_020be260 = scene;
}


