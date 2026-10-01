#include "nitro/types.h"

typedef struct MenuContext {
    u32 unk_00;
    u8 state[4];
} MenuContext;

extern MenuContext *data_ov001_020a0484;
extern void func_ov001_0206b95c(void *state, u8 *out);

void ReadActiveMenuState_0206c328(u8 *out)
{
    if (data_ov001_020a0484 == NULL) {
        *out = 0;
        return;
    }
    func_ov001_0206b95c(data_ov001_020a0484->state, out);
}
