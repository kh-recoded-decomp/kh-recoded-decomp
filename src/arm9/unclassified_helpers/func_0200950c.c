#include "nitro/types.h"

typedef struct {
    s32 *dataPtr;
    volatile u32 flags;
    u8 pad_08[0x514];
    u32 unk_51c;
} Context_0200950c;

typedef struct {
    u8 pad_00[4];
    u32 unk_04;
} GlobalBlock_02056b6c;

extern GlobalBlock_02056b6c data_02056b6c;
extern void func_02002aa8(int mode);
extern void func_02003414(void *ptr, u32 size);
extern void func_0200344c(void *ptr, u32 size);
extern void func_02003470(void);
extern u32 func_02004938(void);
extern void func_0200494c(u32 value);
extern void func_020049b4(u32 value);
extern int func_0200e2e8(int slot, int arg1);
extern int func_0200e30c(int slot, u32 value, int arg2);
extern BOOL Retry_0200950c(Context_0200950c *context, int channel, int retryCount);

BOOL func_0200950c(Context_0200950c *context, int channel, int retryCount)
{
    int result;
    u32 flags;
    u32 value;

    if ((context->flags & 2) == 0) {
        context->flags |= 2;
        result = func_0200e2e8(0xb, 1);
        while (result == 0) {
            func_020049b4(0x32);
            result = func_0200e2e8(0xb, 1);
        }
        Retry_0200950c(context, 0, 1);
    }
    func_0200344c(context->dataPtr, 0x60);
    func_02003470();
    context->unk_51c = data_02056b6c.unk_04;
    do {
        context->flags = context->flags | 0x20;
        do {
            result = func_0200e30c(0xb, channel, 1);
        } while (result < 0);
        if (channel == 0) {
            value = (u32)context->dataPtr;
            do {
                result = func_0200e30c(0xb, value, 1);
            } while (result < 0);
        }
        value = func_02004938();
        flags = context->flags;
        while ((flags & 0x20) != 0) {
            func_02002aa8(0);
            flags = context->flags;
        }
        func_0200494c(value);
        func_02003414(context->dataPtr, 0x60);
    } while ((*context->dataPtr == 4) && (retryCount = retryCount - 1, 0 < retryCount));
    return *context->dataPtr == 0;
}
