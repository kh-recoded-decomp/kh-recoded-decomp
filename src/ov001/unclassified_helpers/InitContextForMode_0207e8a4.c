#include "nitro/types.h"

typedef s32 (*ModeUpdateFunc)(void);

extern s32 *data_ov001_020a04d4;
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov001_0207e130(s32 *context, s32 flag);
extern void func_ov001_0207e244(s32 *context, s32 flag);
extern void func_ov001_0207e270(s32 *context, s32 flag);
extern s32 func_ov001_0207e920(void);
extern s32 func_ov001_0207e9b8(void);

ModeUpdateFunc InitContextForMode_0207e8a4(s32 mode)
{
    ModeUpdateFunc update = NULL;
    s32 *context;

    context = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov001_020a04d4 = context;
    *context = mode;
    switch (mode) {
    case 0:
        break;
    case 1:
        func_ov001_0207e130(context, 1);
        update = func_ov001_0207e920;
        break;
    case 2:
        func_ov001_0207e244(context, 1);
        update = func_ov001_0207e9b8;
        break;
    case 3:
        func_ov001_0207e270(context, 1);
        update = func_ov001_0207e9b8;
        break;
    }
    return update;
}
