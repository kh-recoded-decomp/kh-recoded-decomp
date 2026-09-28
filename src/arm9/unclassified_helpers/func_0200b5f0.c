#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int *ptr;
} Context;

extern int func_0200d01c(Context *self, int *outResult);
extern int func_0200a930(Context *self, int a, int b);

int func_0200b5f0(Context *self, int unused1, int unused2, int unused3) {
    int result = 0;
    int status = func_0200d01c(self, &result);

    if (status == 0) {
        int value;
        self->ptr = &value;
        value = 0;
        status = func_0200a930(self, 0xf, 1);
        if (status != 0) {
            result = value;
        }
    }
    return result;
}
