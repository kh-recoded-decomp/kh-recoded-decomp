#include "nitro/types.h"

typedef struct Ov024Context {
    u8 pad_00[8];
    void *handle;
} Ov024Context;

extern Ov024Context *data_ov024_020b7540;
extern void func_ov027_020b9bb4(void *handle, int value);

void func_ov024_020b65e8(int value) {
    func_ov027_020b9bb4(data_ov024_020b7540->handle, value);
}
