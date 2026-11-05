#include "src/overlays/ov027/FileLoadQueue.h"

extern void NNS_FndRemoveListObject(FileLoadList *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroyFileLoadRequest(FileLoadRequest *request, BOOL freeBuffer)
{
    NNS_FndRemoveListObject(&FileLoadQueues_GetWork()->completed, request);
    if (freeBuffer && request->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(request->buffer);
        request->buffer = NULL;
    }
    if ((u32)request->pathOrId & 0x80000000) {
        request->pathOrId = NULL;
    } else if (request->pathOrId != NULL) {
        NNSi_FndFreeFromDefaultHeap(request->pathOrId);
        request->pathOrId = NULL;
    }
    if (request != NULL) {
        NNSi_FndFreeFromDefaultHeap(request);
    }
}
