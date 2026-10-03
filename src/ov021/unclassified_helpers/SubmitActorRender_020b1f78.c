#include "nitro/types.h"

typedef struct RenderContext {
    u8 pad_00[8];
    void *queue;
} RenderContext;

extern RenderContext data_ov021_020b56a4;
extern void func_ov001_02091c34(void *queue, void *item);

int SubmitActorRender_020b1f78(u8 *actor)
{
    func_ov001_02091c34(data_ov021_020b56a4.queue, actor + 0x34);
    return 0;
}
