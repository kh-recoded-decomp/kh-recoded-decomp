#include "nitro/types.h"

typedef struct SceneContext SceneContext;
typedef void (*SceneCallback)(void *data, SceneContext *ctx);

struct SceneContext {
    u8 pad_0000[0x10cc];
    SceneCallback callback;
    u8 pad_10d0[4];
    u8 callbackData[4];
};

extern SceneContext *data_ov001_020a046c;

void InvokeSceneCallback_020677fc(void) {
    SceneContext *ctx = data_ov001_020a046c;

    if (ctx->callback != NULL) {
        ctx->callback(ctx->callbackData, ctx);
    }
}
