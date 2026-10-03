#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

extern NNSFndList *data_ov027_020ba3c4;
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);

BOOL IsFileLoadQueueEmpty_020ba1a0(void)
{
    NNSFndList *queue = data_ov027_020ba3c4;
    BOOL empty;

    if (queue == NULL) {
        return FALSE;
    }
    empty = FALSE;
    if (NNS_FndGetNextListObject_02012a38(queue, NULL) == NULL) {
        empty = TRUE;
    }
    return empty;
}
