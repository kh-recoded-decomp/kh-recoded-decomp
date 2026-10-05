#include "nitro/types.h"

typedef struct NNSFndLink {
    void *prevObject;
    void *nextObject;
} NNSFndLink;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef void (*FileLoadCallback)(void *request, void *userData);

typedef struct FileLoadRequest {
    int state;
    char *path;
    int loadId;
    int loadMode;
    void *userData;
    FileLoadCallback callback;
    NNSFndLink link;
    u8 pad_20[0x4];
} FileLoadRequest;

extern NNSFndList *data_ov027_020ba3c4;
extern int data_0205fde4;
extern int data_0205fde0;

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern BOOL IsRecordIdFree_0202c38c(int id);
extern int func_0202c364(char *path, int mode);
extern int func_0202c378(char *path, int mode);
extern void RemoveIntrusiveListObject_020129d8(NNSFndList *list, void *object);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, void *object);

void ProcessFileLoadQueue_020b9fac(void)
{
    NNSFndList *queue = data_ov027_020ba3c4;
    FileLoadRequest *request;

    if (data_0205fde4 != 0 || data_0205fde0 != 0) {
        return;
    }
    request = NNS_FndGetNextListObject_02012a38(queue, NULL);
    if (request == NULL) {
        return;
    }
    switch (request->state) {
    case 0:
        if (IsRecordIdFree_0202c38c(0)) {
            if (request->loadMode != 0) {
                request->loadId = func_0202c378(request->path, 14);
            } else {
                request->loadId = func_0202c364(request->path, 14);
            }
            request->state = 1;
        }
        break;
    case 1:
        if (IsRecordIdFree_0202c38c(request->loadId)) {
            request->state = 2;
            RemoveIntrusiveListObject_020129d8(queue, request);
            AppendIntrusiveListObject_020128d0(queue + 1, request);
            if (request->callback != NULL) {
                request->callback(request, request->userData);
            }
        }
        break;
    }
}
