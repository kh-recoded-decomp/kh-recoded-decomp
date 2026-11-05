#include "src/overlays/ov027/FileLoadQueue.h"
#include "src/filesystem/FileLoaderState.h"

extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ClearOverlayLoadQueues(void)
{
    FileLoadRequest *request;
    FileLoadQueueWork *work;
    FileLoadRequest *next;

    work = FileLoadQueues_GetWork();
    request = NNS_FndGetNextListObject(&work->pending, NULL);
    while (request != NULL) {
        next = NNS_FndGetNextListObject(&work->pending, request);
        if (request->state == 1) {
            SleepIfFileLoaderBusy();
            if (request->buffer != NULL) {
                NNSi_FndFreeFromDefaultHeap(request->buffer);
            }
        }
        NNS_FndRemoveListObject(&work->pending, request);
        if (((u32)request->pathOrId & 0x80000000) != 0) {
            request->pathOrId = NULL;
        } else if (request->pathOrId != NULL) {
            NNSi_FndFreeFromDefaultHeap(request->pathOrId);
        }
        if (request != NULL) {
            NNSi_FndFreeFromDefaultHeap(request);
        }
        request = next;
    }

    request = NNS_FndGetNextListObject(&work->completed, NULL);
    while (request != NULL) {
        next = NNS_FndGetNextListObject(&work->completed, request);
        DestroyFileLoadRequest(request, TRUE);
        request = next;
    }
}
