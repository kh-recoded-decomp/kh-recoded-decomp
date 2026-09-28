#include "nitro/types.h"

extern void *func_0202a178(u32 size);
extern void Text_VSNPrintf_020a4f78(void *dst, const char *format, u32 flags, void *args);
extern void func_ov017_020a3fec(void *obj, void *header);

void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args)
{
    void *header = func_0202a178(8);

    Text_VSNPrintf_020a4f78(header, format, flags | 4, args);
    func_ov017_020a3fec(obj, header);
}
