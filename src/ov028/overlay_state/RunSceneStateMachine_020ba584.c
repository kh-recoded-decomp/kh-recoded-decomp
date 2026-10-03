#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x18];
    int state;
} SceneState;

extern SceneState *data_ov028_020bb380;
extern int (*const data_ov028_020bb318[])(void);

extern void func_ov028_020bae68(s32 mode);
extern void func_ov028_020bae48(void);

int RunSceneStateMachine_020ba584(void) {
    int next;

    do {
        data_ov028_020bb380->flags &= 0x7fff;
        next = data_ov028_020bb318[data_ov028_020bb380->state]();
        if (next >= 0) {
            data_ov028_020bb380->state = next;
        }
    } while (data_ov028_020bb380->flags & 0x8000);
    if (data_ov028_020bb380->flags & 8) {
        func_ov028_020bae68(0);
    }
    if (data_ov028_020bb380->flags & 4) {
        func_ov028_020bae48();
    }
    return 0;
}
