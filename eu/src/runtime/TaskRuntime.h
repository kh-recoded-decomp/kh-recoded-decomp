#ifndef KH_RECODED_TASK_RUNTIME_H
#define KH_RECODED_TASK_RUNTIME_H

#include "nitro/types.h"

/* Native DS layout. Callback/state and heap words are intentionally not host
 * pointers: stateWord also carries -1/-2 sentinels. Decode them in a host port. */
typedef struct TaskObject {
    u32 flags;
    struct TaskObject *parent;
    struct TaskObject *prev;
    struct TaskObject *next;
    u16 classId;
    u16 subId;
    u32 stateWord;
    u32 destructorWord;
    u32 heapWord;
    void *work;
    u32 workSize;
    u32 reserved28;
} TaskObject;

typedef struct TaskManagerState {
    u32 reserved00;
    TaskObject *current;
    u32 updateCount;
    TaskObject *head;
} TaskManagerState;

typedef char TaskObjectNativeSize[(sizeof(TaskObject) == 44) ? 1 : -1];
typedef char TaskObjectWorkOffset[(u32)&((TaskObject *)0)->work == 0x20 ? 1 : -1];
typedef char TaskManagerCurrentOffset[(u32)&((TaskManagerState *)0)->current == 4 ? 1 : -1];

extern TaskManagerState gTaskManager;

TaskObject *GetCurrentTaskObject(void);
void *GetRunningTaskWork(void);
u32 GetTaskUpdateCount(void);
TaskObject *DestroyTaskObjectWrapper(TaskObject *task);

#endif
