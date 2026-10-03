#include "nitro/types.h"

typedef struct FadeParams {
    u8 direction;
    u8 screens;
    u16 speed;
} FadeParams;

typedef struct FadeState {
    s32 frame;
    FadeParams params;
    s32 brightness;
} FadeState;

extern FadeState *data_ov002_0206c468;
extern u8 data_ov002_0206c41c;
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern int func_0202a754(void);
extern int func_ov002_020665e8(void);

void *StartScreenFade_0206656c(FadeParams *params)
{
    data_ov002_0206c468 = NNSi_FndGetCurrentRootHeap_0202a764();
    func_01ff8740(0, data_ov002_0206c468, sizeof(FadeState));
    data_ov002_0206c468->frame = func_0202a754();
    data_ov002_0206c468->params = *params;
    if (data_ov002_0206c468->params.direction == 0) {
        data_ov002_0206c468->brightness = -0x10000;
    }
    data_ov002_0206c41c = 0;
    return func_ov002_020665e8;
}
