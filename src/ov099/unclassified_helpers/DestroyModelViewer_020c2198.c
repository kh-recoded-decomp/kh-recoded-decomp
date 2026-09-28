#include "nitro/types.h"

typedef struct ModelViewer ModelViewer;

extern void func_ov099_020c1d00(ModelViewer *viewer);
extern void FreeModelFiles_020c1b08(ModelViewer *viewer);
extern void func_02006d3c(u32 value);

void DestroyModelViewer_020c2198(ModelViewer *viewer)
{
    func_ov099_020c1d00(viewer);
    FreeModelFiles_020c1b08(viewer);
    func_02006d3c(0);
}
