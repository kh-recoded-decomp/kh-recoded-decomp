#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct FileLoadQueues {
    NNSFndList pending;
    NNSFndList finished;
} FileLoadQueues;

typedef struct FileLoadRequest {
    int state;
    char *path;
    void *buffer;
} FileLoadRequest;

extern FileLoadQueues *data_ov027_020ba3c4;
extern void RemoveIntrusiveListObject_020129d8(NNSFndList *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void DestroyFileLoadRequest_020ba1e0(FileLoadRequest *request, BOOL freeBuffer)
{
    RemoveIntrusiveListObject_020129d8(&data_ov027_020ba3c4->finished, request);
    if (freeBuffer && request->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(request->buffer);
        request->buffer = NULL;
    }
    if ((u32)request->path & 0x80000000) {
        request->path = NULL;
    } else if (request->path != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(request->path);
        request->path = NULL;
    }
    if (request != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(request);
    }
}
