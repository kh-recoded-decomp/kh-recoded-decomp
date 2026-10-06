#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x50];
    u32 value1;
    u32 value2;
    u32 value3;
} ObjectState;

extern u32 func_ov016_020a1e84();
extern void func_ov016_020a2084(ObjectState *obj, u32 source, u32 *cursor);
extern u32 func_ov001_0208723c(u32 value);
extern void func_ov016_020a6358();

u32 func_ov016_020a20ac(u32 messageId, u32 arg1, u32 unused, u32 arg2)
{
    u32 context;
    ObjectState buffer;
    u32 cursor;
    u32 extra;

    cursor = arg1;
    extra = arg2;
    context = func_ov016_020a1e84(&buffer, messageId, &cursor);
    func_ov016_020a2084(&buffer, messageId, &cursor);
    context = func_ov001_0208723c(context);
    func_ov016_020a6358(context, &buffer);
    return 1;
}
