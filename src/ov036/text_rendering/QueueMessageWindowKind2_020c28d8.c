#include "nitro/types.h"

typedef struct WindowSize {
    s32 width;
    s32 height;
} WindowSize;

typedef struct MessageRequest {
    s32 x;
    s32 y;
    WindowSize *size;
    s32 style;
    u16 *text;
    s32 portraitId;
    s32 portraitPose;
    s32 kind;
} MessageRequest;

extern void QueueMessageWindow_020c2610(MessageRequest *request);

void QueueMessageWindowKind2_020c28d8(MessageRequest *request) {
    request->kind = 2;
    request->size = NULL;
    QueueMessageWindow_020c2610(request);
}
