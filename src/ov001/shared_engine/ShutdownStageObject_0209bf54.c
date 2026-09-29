#include "nitro/types.h"

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

typedef struct {
    u8 pad_00[0x78];
    u32 isActive;
} ObjBase;

typedef struct {
    u8 pad_00[0x10];
    ObjBase base;
} StageObject;

extern StageManager *g_stageManager_020a0508;
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern void func_02035c48(StageObject *obj);
extern void func_020359b0(StageObject *obj);
extern void Obj_ShutdownBase_02035554(void *entity);

void ShutdownStageObject_0209bf54(StageObject *obj)
{
    StageManager *manager;
    ObjBase *base = &obj->base;

    if (base->isActive == 0) {
        return;
    }
    base->isActive = 0;
    manager = g_stageManager_020a0508;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = func_0202a158();
        SetDefaultHeap_0202a134(manager->heapScope.objectHeap);
    }
    func_02035c48(obj);
    func_020359b0(obj);
    manager = g_stageManager_020a0508;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap_0202a134(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
    Obj_ShutdownBase_02035554(&obj->base);
}
