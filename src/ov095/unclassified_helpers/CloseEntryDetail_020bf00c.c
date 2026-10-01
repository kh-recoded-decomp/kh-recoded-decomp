#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0x11108];
    int detailOpen;
} EntryViewer;

extern void func_ov095_020bfa18(int mode, EntryViewer *viewer);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void CloseEntryDetail_020bf00c(EntryViewer *viewer)
{
    if (viewer->detailOpen != TRUE) {
        return;
    }
    viewer->detailOpen = FALSE;
    func_ov095_020bfa18(1, viewer);
    PlaySoundEffect_0204d924(0, 2);
}
