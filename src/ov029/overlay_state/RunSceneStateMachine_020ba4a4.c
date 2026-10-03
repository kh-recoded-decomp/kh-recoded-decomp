#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0xc];
    int state;
} SceneState;

extern SceneState *data_ov029_020baba0;
extern int (*const data_ov037_020bab78[])(void);

extern void func_ov029_020ba86c(int mode);
extern void func_ov029_020ba84c(void);

int RunSceneStateMachine_020ba4a4(void) {
    int next;

    do {
        data_ov029_020baba0->flags &= 0x7fff;
        next = data_ov037_020bab78[data_ov029_020baba0->state]();
        if (next >= 0) {
            data_ov029_020baba0->state = next;
        }
    } while (data_ov029_020baba0->flags & 0x8000);
    if (data_ov029_020baba0->flags & 8) {
        func_ov029_020ba86c(0);
    }
    if (data_ov029_020baba0->flags & 4) {
        func_ov029_020ba84c();
    }
    return 0;
}
