#include "nitro/types.h"

typedef struct StageQuad {
    u8 pad_00[0x8];
    void *resource;
    u8 pad_0c[0x2a - 0xc];
    u8 alpha : 5;
    u8 flags : 3;
} StageQuad;

typedef struct StageManager {
    u8 pad_00000[0x18d9c];
    void *quadList;
} StageManager;

extern StageManager *g_stageManager_020a0508;
extern void *func_ov001_0208f27c(void *list);
extern void *func_ov001_0208f28c(void *node);
extern StageQuad *BindDescriptor0_0208f268(void *list, void *node);
extern void NNS_FndInitListWithOffset0_0206ad28(StageQuad *quad);

void DrawVisibleStageQuads_02099a84(void)
{
    void *node;
    StageQuad *quad;

    for (node = func_ov001_0208f27c(g_stageManager_020a0508->quadList); node != NULL;
         node = func_ov001_0208f28c(node)) {
        quad = BindDescriptor0_0208f268(g_stageManager_020a0508->quadList, node);
        if (quad->resource != NULL && quad->alpha != 0) {
            NNS_FndInitListWithOffset0_0206ad28(quad);
        }
    }
}
