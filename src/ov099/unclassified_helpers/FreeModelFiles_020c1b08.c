#include "nitro/types.h"

typedef struct {
    void *modelData;
    void *models[40];
    void *sourceFile;
} ModelViewer;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ZeroHalfThenFree_0202cd78(void *file);

void FreeModelFiles_020c1b08(ModelViewer *viewer)
{
    NNSi_FndFreeFromDefaultHeap_0202a1c4(viewer->modelData);
    ZeroHalfThenFree_0202cd78(viewer->sourceFile);
}
