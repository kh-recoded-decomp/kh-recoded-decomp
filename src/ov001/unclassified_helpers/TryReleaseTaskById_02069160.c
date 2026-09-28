#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    u8 pad_08[0x39];
    s8 locked;
} TaskNode;

typedef struct TaskManager TaskManager;

extern TaskManager *data_ov001_020a0478;
extern TaskNode *FindTaskNodeById_02069014(TaskManager *manager, u16 id);
extern TaskNode *ReleaseTaskNode_02069030(TaskNode *node);

BOOL TryReleaseTaskById_02069160(int id)
{
    TaskManager *manager = data_ov001_020a0478;

    if (FindTaskNodeById_02069014(manager, id)->locked != 0) {
        return FALSE;
    }
    ReleaseTaskNode_02069030(FindTaskNodeById_02069014(manager, id));
    return TRUE;
}
