#include "nitro/types.h"

typedef struct CursorState {
    u8 pad_00[0x18];
    u32 flags;
    u8 pad_1c[0x54 - 0x1c];
    s8 mode;
} CursorState;

extern CursorState *data_ov015_020812e0;
extern int func_ov015_02077df0(void);
extern int func_ov015_02077c60(void);
extern int func_ov015_02077a8c(void);

int UpdateCursorMode_02077a28(void)
{
    int result = 0;
    CursorState *cursor = data_ov015_020812e0;

    if (!(cursor->flags & 1)) {
        if (cursor->mode == 4) {
            result = func_ov015_02077df0();
        } else if (cursor->mode == 3) {
            result = func_ov015_02077c60();
        } else {
            result = func_ov015_02077a8c();
        }
        if (result != 0) {
            data_ov015_020812e0->flags |= 1;
        }
    }
    return result;
}
