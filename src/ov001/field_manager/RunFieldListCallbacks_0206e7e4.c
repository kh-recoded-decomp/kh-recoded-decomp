#include "nitro/types.h"

typedef struct FieldCallbackNode {
    void (*callback)(void);
} FieldCallbackNode;

typedef struct FieldManager {
    u8 pad_000[0x5d0];
    u8 callbackList[0xc];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 active;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);

void RunFieldListCallbacks_0206e7e4(void)
{
    FieldManager *manager = data_ov001_020a04a4.manager;
    FieldCallbackNode *node;

    if (data_ov001_020a04a4.active == 0) {
        return;
    }
    for (node = NNS_FndGetNextListObject_02012a38(manager->callbackList, NULL); node != NULL;
         node = NNS_FndGetNextListObject_02012a38(manager->callbackList, node)) {
        node->callback();
    }
}
