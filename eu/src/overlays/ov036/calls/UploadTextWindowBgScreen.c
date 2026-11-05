#include "nitro/types.h"

typedef void (*HandlerFunc)(void *target, u32 arg0, u32 arg1);

typedef struct {
    u8 pad_00[0xC];
    u8 body[1];
} HandlerOwner;

extern HandlerFunc gTextSceneBgScreenLoaders[];

void UploadTextWindowBgScreen(int handlerIndex, HandlerOwner *owner, u32 arg0, u32 arg1) {
    gTextSceneBgScreenLoaders[handlerIndex](owner->body, arg0, arg1);
}
