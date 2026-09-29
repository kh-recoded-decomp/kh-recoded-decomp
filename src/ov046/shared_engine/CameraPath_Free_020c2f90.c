#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPath {
    void *nodes;
    u16 nodeCount;
    u8 pad_06[0x46];
    s32 curveType;
    fx32 duration;
    void *links;
    u16 linkCount;
} CameraPath;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void CameraPath_Free_020c2f90(CameraPath *path)
{
    NNSi_FndFreeFromDefaultHeap_0202a1c4(path->nodes);
    path->nodes = NULL;
    if (path->links != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(path->links);
        path->links = NULL;
    }
}
