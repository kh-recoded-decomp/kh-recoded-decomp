#include "nitro/types.h"

typedef struct ListSource {
    u8 pad_00[0xc];
    int nameId;
} ListSource;

typedef struct ListLoader {
    u8 pad_00[4];
    ListSource *source;
    BOOL loadAsync;
    int layoutArg;
} ListLoader;

typedef char *(*PathResolver)(int nameId);

extern void *QueueFileLoadRequest_020ba114(char *path, int loadMode, void (*callback)(void *, void *), void *userData);
extern void *func_0202c48c(char *path, int heapTag);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov073_020c3530(ListLoader *loader, void *file, int layoutArg);
extern void func_ov073_020c3684(void *request, void *userData);

void LoadListLayoutFile_020c36a4(ListLoader *loader, PathResolver resolvePath)
{
    char *path = resolvePath(loader->source->nameId);
    void *file;

    if (loader->loadAsync) {
        QueueFileLoadRequest_020ba114(path, 1, func_ov073_020c3684, loader);
        return;
    }
    file = func_0202c48c(path, 0xe);
    func_ov073_020c3530(loader, file, loader->layoutArg);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
