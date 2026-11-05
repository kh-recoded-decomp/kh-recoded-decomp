#include "src/overlays/ov027/FileLoadQueue.h"

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuFill8(void *dest, int value, u32 size);
extern int STD_GetStringLength(const char *str);
extern char *STD_CopyString(char *destp, const char *srcp);
extern void NNS_FndAppendListObject(FileLoadList *list, void *object);

FileLoadRequest *QueueFileLoadRequest(char *path, int loadMode, FileLoadCallback callback, void *userData) {
    FileLoadRequest *request;
    char *pathCopy;

    request = NNS_FndAllocFromDefaultExpHeapEx(sizeof(FileLoadRequest), -4);
    MI_CpuFill8(request, 0, sizeof(FileLoadRequest));
    if ((u32)path & 0x80000000) {
        request->pathOrId = path;
    } else {
        pathCopy = NNS_FndAllocFromDefaultExpHeapEx(STD_GetStringLength(path) + 1, -4);
        request->pathOrId = pathCopy;
        STD_CopyString(pathCopy, path);
    }
    request->callback = callback;
    request->userData = userData;
    request->loadMode = loadMode;
    NNS_FndAppendListObject(&FileLoadQueues_GetWork()->pending, request);
    return request;
}
