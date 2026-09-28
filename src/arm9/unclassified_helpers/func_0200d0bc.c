#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 base;
    u32 size;
    u32 base2;
    u32 size2;
    u8 pad_14[8];
    u32 memPtr;
} TableInfo;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
    u8 pad_18[8];
    TableInfo *info;
} Context;

extern int func_0200d290(void);
extern void func_0200d1fc(Context *ctx);
extern void func_0200b394(void *fileObj);
extern int func_0200b494(void *fileObj, Context *ctx, u32 start, u32 end, u32 index);
extern int func_0200b674(void *fileObj, u32 dst, u32 len);
extern void func_01ff8830(u32 dst, u32 value, u32 len);
extern void func_0200b5b0(void *fileObj);

u32 func_0200d0bc(Context *ctx, u32 memAddr, u32 maxSize)
{
    u8 fileObj[72];
    TableInfo *info;
    u32 totalSize;
    u32 dest1;
    u32 dest2;

    if (memAddr != 0 && func_0200d290() != 0) {
        func_0200d1fc(ctx);
    }

    info = ctx->info;
    totalSize = (info->size + info->size2 + 0x3f) & ~0x1f;
    if (totalSize <= maxSize) {
        dest1 = (memAddr + 0x1f) & ~0x1f;

        func_0200b394(fileObj);
        if (func_0200b494(fileObj, ctx, info->base, info->base + info->size, 0xffffffff) != 0) {
            if (func_0200b674(fileObj, dest1, info->size) < 0) {
                func_01ff8830(dest1, 0, info->size);
            }
            func_0200b5b0(fileObj);
        }
        info->base = dest1;
        dest2 = dest1 + info->size;

        if (func_0200b494(fileObj, ctx, info->base2, info->base2 + info->size2, 0xffffffff) != 0) {
            if (func_0200b674(fileObj, dest2, info->size2) < 0) {
                func_01ff8830(dest2, 0, info->size2);
            }
            func_0200b5b0(fileObj);
        }
        info->base2 = dest2;

        info->memPtr = memAddr;
        ctx->flags |= 4;
    }
    return totalSize;
}
