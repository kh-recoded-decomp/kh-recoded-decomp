#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct TexVramUsage {
    s32 usedSize;
    s32 totalSize;
} TexVramUsage;

extern void func_0201377c(int index, u32 startAddr, u32 endAddr, u32 blockMax, BOOL active, void *userContext);
extern void NNS_GfdDumpFrmTexVramManagerEx_02013824(NNSGfdFrmTexVramDebugDumpCallBack callback, void *userContext);

void NNS_GfdDumpFrmTexVramManager_020137f8(void)
{
    TexVramUsage usage = {0, 0};

    NNS_GfdDumpFrmTexVramManagerEx_02013824(func_0201377c, &usage);
}
