#include "nitro/types.h"

typedef struct ClassDescriptor {
    u16 classId;
    u16 subId;
    void *(*construct)(void *arg);
    void *method;
    u32 workSize;
    void ***heapRef;
} ClassDescriptor;

typedef struct TaskObject {
    u32 flags;
    struct TaskObject *parent;
    struct TaskObject *prev;
    struct TaskObject *next;
    u16 classId;
    u16 subId;
    void *state;
    void *method;
    void **heap;
    void *work;
    u32 workSize;
    u32 unk_28;
} TaskObject;

typedef struct TaskManager {
    u32 unk_00;
    TaskObject *current;
} TaskManager;

extern TaskManager data_020603c8;
extern void *SetDefaultHeap_0202a134(void *heap);
extern void *NNSi_FndAllocFromExpHeapEx_0202a1e4(u32 size, void **heap);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void MI_CpuFill8_01ff8830(void *dst, int value, u32 size);
extern void LinkRegisteredObject_0202a290(TaskObject *object);

TaskObject *Obj_Construct_0202a4b0(TaskObject *object, ClassDescriptor *desc, void *ctorArg, int useTailAlloc)
{
    void **heap;
    void *savedHeap;
    TaskObject *savedCurrent;

    heap = NULL;
    object->flags = 0;
    object->parent = data_020603c8.current;
    object->classId = desc->classId;
    object->subId = desc->subId;
    if (desc->heapRef != NULL) {
        heap = *desc->heapRef;
    }
    object->heap = heap;
    object->workSize = desc->workSize;
    object->state = NULL;
    object->method = desc->method;
    object->unk_28 = 0;
    savedHeap = SetDefaultHeap_0202a134(heap);
    if (object->workSize != 0) {
        if (useTailAlloc != 0) {
            object->work = AllocFromHeapOrDefaultEx_0202a210(object->workSize, -4, object->heap);
        } else {
            object->work = NNSi_FndAllocFromExpHeapEx_0202a1e4(object->workSize, object->heap);
        }
        MI_CpuFill8_01ff8830(object->work, 0, object->workSize);
    } else {
        object->work = NULL;
    }
    LinkRegisteredObject_0202a290(object);
    savedCurrent = data_020603c8.current;
    data_020603c8.current = object;
    data_020603c8.current->state = desc->construct(ctorArg);
    data_020603c8.current = savedCurrent;
    SetDefaultHeap_0202a134(savedHeap);
    return object;
}
