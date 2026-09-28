#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x50];
    u32 value1;
    u32 value2;
    u32 value3;
} ObjectState;

extern u32 func_ov016_020a1e64();
extern void func_ov016_020a2064(ObjectState *obj, u32 source, u32 *cursor);
extern u32 func_ov001_02087214(u32 value);
extern void func_ov016_020a6338();

u32 func_ov016_020a208c(u32 messageId, u32 arg1, u32 unused, u32 arg2)
{
    u32 context;
    ObjectState buffer;
    u32 cursor;
    u32 extra;

    cursor = arg1;
    extra = arg2;
    context = func_ov016_020a1e64(&buffer, messageId, &cursor);
    func_ov016_020a2064(&buffer, messageId, &cursor);
    context = func_ov001_02087214(context);
    func_ov016_020a6338(context, &buffer);
    return 1;
}
