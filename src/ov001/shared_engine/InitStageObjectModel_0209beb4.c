#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u8 pad_00[0x18e14];
    HeapScope heapScope;
} StageManager;

typedef struct ModelHeader {
    u16 unk_00;
    u16 version;
} ModelHeader;

typedef struct ModelDef {
    ModelHeader *header;
    u8 pad_04[0x7c];
    u32 resource;
    u8 pad_84[0x6c];
    void *textureInfo;
} ModelDef;

typedef struct StageObject {
    u8 pad_000[0x14];
    u8 textureDest[0xd8];
    u8 textureSrc[0xd8];
    u16 unk_1c4;
} StageObject;

extern StageManager *g_stageManager_020a0508;
extern const VecFx32 data_02053438;
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern BOOL func_02035930(StageObject *object, u32 resource, u32 param3, u32 param4);
extern BOOL func_0202ea38(void *dst, void *src, void *info);
extern void ActorSlot_PlaceAndLink_02035a18(StageObject *object, int anchor, const VecFx32 *offset);

void InitStageObjectModel_0209beb4(StageObject *object, ModelDef *def)
{
    StageManager *manager = g_stageManager_020a0508;

    if (manager == NULL || def == NULL) {
        return;
    }
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = func_0202a158();
        SetDefaultHeap_0202a134(manager->heapScope.objectHeap);
    }
    object->unk_1c4 = 0;
    func_02035930(object, def->resource, 0, 0xb);
    if (def->header->version > 3) {
        func_0202ea38(object->textureSrc, object->textureDest, def->textureInfo);
    }
    ActorSlot_PlaceAndLink_02035a18(object, 0, &data_02053438);
    manager = g_stageManager_020a0508;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap_0202a134(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}
