#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    u8 pad_08[0x48];
    u16 id;
} TaskNode;

typedef struct TaskManager {
    u16 activeIds[8];
    u8 activeCount;
    u8 pad_11[0x23];
    TaskNode *head;
} TaskManager;

extern TaskManager *data_ov001_020a0478;
extern TaskNode *ReleaseTaskNode_02069030(TaskNode *node);
extern void func_01ff8684(u32 value, void *dest, u32 size);

void ReleaseLowIdTaskNodes_02069194(void)
{
    TaskNode *node = data_ov001_020a0478->head->next;

    while (node != NULL) {
        if (node->id >= 0xf8) {
            node = node->next;
        } else {
            node = ReleaseTaskNode_02069030(node);
        }
    }
    func_01ff8684(0xffff, data_ov001_020a0478->activeIds, sizeof(data_ov001_020a0478->activeIds));
    data_ov001_020a0478->activeCount = 0;
}
