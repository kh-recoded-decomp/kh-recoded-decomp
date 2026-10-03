#include "nitro/types.h"

extern void func_ov075_020cf458(void *dialog, void *owner, s16 x, u16 y, u16 width, u16 height, int duration,
                                void *text, int flags);

void OpenDefaultDialog_020cf430(void *dialog, void *owner, s16 x, u16 y, u16 width, u16 height, void *text)
{
    func_ov075_020cf458(dialog, owner, x, y, width, height, 0x96, text, 0x412);
}