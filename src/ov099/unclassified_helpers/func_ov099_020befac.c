#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int scrollTop;
    int cursorRow;
    u8 pad_34[0x4c - 0x34];
} ListState;

typedef struct {
    u8 pad_0000[0xcf04];
    int selectedEntry;
    u8 pad_cf08[0xd054 - 0xcf08];
    ListState lists[1];
} ViewerWork;

extern BOOL func_ov099_020c1014(int listIndex, ViewerWork *work);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov099_020c156c(ViewerWork *work);
extern void func_ov099_020bf818(int listIndex, ViewerWork *work);
extern void func_ov091_020c1760(int mode, ViewerWork *work);

void func_ov099_020befac(ViewerWork *work)
{
    ListState *list;

    if (!func_ov099_020c1014(0, work)) {
        return;
    }
    list = &work->lists[0];
    work->selectedEntry = list->scrollTop + list->cursorRow;
    PlaySoundEffect_0204d924(0, 0);
    func_ov099_020c156c(work);
    func_ov099_020bf818(0, work);
    func_ov091_020c1760(1, work);
}
