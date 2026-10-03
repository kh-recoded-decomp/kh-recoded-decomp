#include "nitro/types.h"

typedef struct FieldTask {
    u8 pad_00[0x11];
    s8 linkA;
    s8 linkB;
    u8 pad_13[0x1d];
} FieldTask;

typedef struct TaskNode TaskNode;

struct TaskNode {
    TaskNode *prev;
    TaskNode *next;
    FieldTask task;
    u8 pad_38[0x18];
    u16 id;
    u8 pad_52;
    u8 config;
};

typedef struct TriggerQueue {
    u8 pad_00[0x14];
    int usedBits[8];
    TaskNode *head;
} TriggerQueue;

extern TriggerQueue *data_ov001_020a0478;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void func_01ff86fc(u32 value, void *dest, u32 size);
extern void func_0202d44c(int *bitWords, int bitIndex);
extern void InitRangeTriggerNode_020697ac(FieldTask *task, void *params);
extern void InitOffsetFieldTask_020698bc(FieldTask *task, void *params);
extern void func_ov001_02069a54(FieldTask *task, void *params);
extern void InitModeFieldTask_02069be8(FieldTask *task, void *params);
extern void InitModeFieldTask_02069c8c(FieldTask *task, void *params);
extern void InitFieldTask_02069d10(FieldTask *task, void *params);
extern void InitPairFieldTask_02069e84(FieldTask *task, void *params);
extern void InitModeFieldTask_02069f04(FieldTask *task, void *params);
extern void func_ov007_020a1bd0(FieldTask *task, void *params);

void CreateFieldTaskNode_02069274(u32 id, BOOL isSecondary, int type, void *params)
{
    TriggerQueue *queue = data_ov001_020a0478;
    TaskNode *node;
    TaskNode *tail;
    FieldTask *task;

    if (isSecondary) {
        id += 0xf8;
    }
    node = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(TaskNode));
    func_01ff8740(0, node, sizeof(TaskNode));
    func_0202d44c(queue->usedBits, id);
    tail = queue->head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    node->prev = tail;
    task = &node->task;
    func_01ff86fc(0, task, sizeof(FieldTask));
    task->linkA = -1;
    task->linkB = -1;
    switch (type) {
    case 0:
        InitRangeTriggerNode_020697ac(task, params);
        break;
    case 1:
        InitOffsetFieldTask_020698bc(task, params);
        break;
    case 2:
        func_ov001_02069a54(task, params);
        break;
    case 3:
        InitModeFieldTask_02069be8(task, params);
        break;
    case 4:
        InitModeFieldTask_02069c8c(task, params);
        break;
    case 6:
        InitFieldTask_02069d10(task, params);
        break;
    case 7:
        InitPairFieldTask_02069e84(task, params);
        break;
    case 8:
        InitModeFieldTask_02069f04(task, params);
        break;
    case 9:
        func_ov007_020a1bd0(task, params);
        break;
    }
    node->config |= 1;
    node->id = id;
}
