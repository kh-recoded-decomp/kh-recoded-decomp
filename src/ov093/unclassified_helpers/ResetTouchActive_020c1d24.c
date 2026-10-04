#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1c4];
    int touchActive;
} SceneWork;

extern SceneWork *data_ov093_020c50e0;
extern void func_ov039_020bc03c(int value);

void ResetTouchActive_020c1d24(void)
{
    data_ov093_020c50e0->touchActive = 0;
    func_ov039_020bc03c(0);
}
