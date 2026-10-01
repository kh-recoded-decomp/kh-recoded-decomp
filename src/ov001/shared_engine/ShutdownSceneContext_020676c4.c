#include "nitro/types.h"

typedef struct SceneContext {
    u8 pad_0000[0xd];
    s8 currentId;
    s8 previousId;
    u8 flags;
    u8 pad_0010[4];
    void *buffer;
    u8 pad_0018[0x10b8 - 0x18];
    u8 loaded;
} SceneContext;

extern SceneContext *data_ov001_020a046c;
extern void func_ov001_02067a6c(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void ShutdownAllActorSlots_0203666c(void);

void ShutdownSceneContext_020676c4(void)
{
    SceneContext *ctx = data_ov001_020a046c;

    func_ov001_02067a6c();
    if (ctx->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(ctx->buffer);
        ctx->buffer = NULL;
    }
    ShutdownAllActorSlots_0203666c();
    ctx->loaded = 0;
    ctx->flags &= ~3;
    ctx->previousId = ctx->currentId;
    ctx->currentId = -1;
}
