#include "nitro/types.h"

extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov077_020c6c90(void *work, BOOL restoreElements);

int CancelAndCloseMenu_020c79a4(void *work)
{
    PlaySoundEffect_0204d924(1, 3);
    func_ov077_020c6c90(work, TRUE);
    return 3;
}
