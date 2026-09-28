#include "nitro/types.h"

typedef struct PendingRequest {
    u8 pending : 1;
    u8 arg;
    u16 id;
} PendingRequest;

typedef struct Context {
    u8 pad_000[0x90c];
    PendingRequest request;
} Context;

extern Context *data_ov001_020a04cc;

void PostPendingRequest_0207d630(u16 requestId, u8 requestArg)
{
    PendingRequest *request;

    request = &data_ov001_020a04cc->request;
    request->pending = 1;
    request->id = requestId;
    request->arg = requestArg;
}
