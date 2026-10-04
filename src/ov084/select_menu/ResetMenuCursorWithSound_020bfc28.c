#include "nitro/types.h"

extern void func_ov039_020bbf78(int a, int b, int c);
extern void PlaySoundEffect_0204d924(int channel, int id);

void ResetMenuCursorWithSound_020bfc28(void)
{
    func_ov039_020bbf78(-1, -1, 1);
    PlaySoundEffect_0204d924(0, 3);
}
