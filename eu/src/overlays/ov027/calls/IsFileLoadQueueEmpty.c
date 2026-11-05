#include "src/overlays/ov027/FileLoadQueue.h"

extern void *NNS_FndGetNextListObject(void *list, void *obj);

BOOL IsFileLoadQueueEmpty(void)
{
    FileLoadList *queue = (FileLoadList *)FileLoadQueues_GetWork();
    BOOL empty;

    if (queue == NULL) {
        return FALSE;
    }
    empty = FALSE;
    if (NNS_FndGetNextListObject(queue, NULL) == NULL) {
        empty = TRUE;
    }
    return empty;
}
