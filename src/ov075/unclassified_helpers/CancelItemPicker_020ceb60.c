#include "nitro/types.h"

typedef struct ItemPicker ItemPicker;

extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov075_020cde4c(ItemPicker *picker, BOOL closing);

s32 CancelItemPicker_020ceb60(ItemPicker *picker)
{
    PlaySoundEffect_0204d924(1, 3);
    func_ov075_020cde4c(picker, TRUE);
    return 3;
}
