#include "src/overlays/ov027/FileLoadQueue.h"

extern int gPanelActive;
extern int gPreviousPanelActive;

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern BOOL IsRecordIdFree(int id);
extern void *RequestFileLoadFromHeapHead(char *path, int mode);
extern void *RequestFileLoadFromHeapTail(char *path, int mode);
extern void NNS_FndRemoveListObject(FileLoadList *list, void *object);
extern void NNS_FndAppendListObject(FileLoadList *list, void *object);

void ProcessFileLoadQueue(void)
{
    FileLoadList *queue = (FileLoadList *)FileLoadQueues_GetWork();
    FileLoadRequest *request;

    if (gPanelActive != 0 || gPreviousPanelActive != 0) {
        return;
    }
    request = NNS_FndGetNextListObject(queue, NULL);
    if (request == NULL) {
        return;
    }
    switch (request->state) {
    case 0:
        if (IsRecordIdFree(0)) {
            if (request->loadMode != 0) {
                request->buffer = RequestFileLoadFromHeapTail(request->pathOrId, 14);
            } else {
                request->buffer = RequestFileLoadFromHeapHead(request->pathOrId, 14);
            }
            request->state = 1;
        }
        break;
    case 1:
        if (IsRecordIdFree((s32)request->buffer)) {
            request->state = 2;
            NNS_FndRemoveListObject(queue, request);
            NNS_FndAppendListObject(queue + 1, request);
            if (request->callback != NULL) {
                request->callback(request, request->userData);
            }
        }
        break;
    }
}
