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
    void *buffer;
    int loadMode;
    void *userData;
    FileLoadCallback callback;
    NNSFndLink link;
    u8 pad_20[0x4];
} FileLoadRequest;

extern NNSFndList *data_ov027_020ba3c4;

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_01ff8830(void *dest, int value, u32 size);
extern int Strlen_02010c74(const char *str);
extern char *STD_CopyString_02010ba4(char *destp, const char *srcp);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, void *object);

FileLoadRequest *QueueFileLoadRequest_020ba114(char *path, int loadMode, FileLoadCallback callback, void *userData) {
    FileLoadRequest *request;
    char *pathCopy;

    request = NNSi_FndAllocFromDefaultHeapEx_0202a19c(sizeof(FileLoadRequest), -4);
    func_01ff8830(request, 0, sizeof(FileLoadRequest));
    if ((u32)path & 0x80000000) {
        request->path = path;
    } else {
        pathCopy = NNSi_FndAllocFromDefaultHeapEx_0202a19c(Strlen_02010c74(path) + 1, -4);
        request->path = pathCopy;
        STD_CopyString_02010ba4(pathCopy, path);
    }
    request->callback = callback;
    request->userData = userData;
    request->loadMode = loadMode;
    AppendIntrusiveListObject_020128d0(data_ov027_020ba3c4, request);
    return request;
}
