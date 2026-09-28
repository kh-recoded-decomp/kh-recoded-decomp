#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 field_0c;
    u8 *field_10;
    u32 field_14;
} InnerData;

typedef struct {
    InnerData *dataPtr;
} Context;

extern BOOL func_0200950c(Context *context, int channel, int retryCount);
extern u8 data_02057520;

void func_020099a4(Context *context, int p2, int p3, int p4) {
    func_0200950c(context, 2, 1);
    context->dataPtr->field_0c = 0;
    context->dataPtr->field_10 = &data_02057520;
    context->dataPtr->field_14 = 1;
    func_0200950c(context, 6, 1);
}
