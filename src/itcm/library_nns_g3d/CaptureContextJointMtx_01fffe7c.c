#include "nitro/types.h"

typedef struct JointMatrixCache JointMatrixCache;

typedef struct RenderOwner {
    u8 pad_00[0x2c];
    JointMatrixCache *matrixCache;
} RenderOwner;

typedef struct RenderContext {
    u8 pad_00[4];
    RenderOwner *owner;
} RenderContext;

extern void CaptureSelectedJointMtx_01fffe28(JointMatrixCache *cache, RenderContext *context);

void CaptureContextJointMtx_01fffe7c(RenderContext *context) {
    CaptureSelectedJointMtx_01fffe28(context->owner->matrixCache, context);
}
