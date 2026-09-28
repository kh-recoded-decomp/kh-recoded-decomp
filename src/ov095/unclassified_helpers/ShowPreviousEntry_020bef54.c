#include "nitro/types.h"

extern BOOL func_ov095_020c1060(void *viewer);
extern void func_ov095_020bfa18(int mode, void *viewer);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ShowPreviousEntry_020bef54(void *viewer)
{
    if (!func_ov095_020c1060(viewer)) {
        return;
    }
    func_ov095_020bfa18(1, viewer);
    PlaySoundEffect_0204d924(0, 0);
}
