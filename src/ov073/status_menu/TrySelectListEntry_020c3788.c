#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x80];
    u8 *entryStates;
} ListView;

extern void SelectListEntry_020c3718(ListView *list, int entryIndex);
extern BOOL func_ov073_020c32a8(ListView *list, int entryIndex);

BOOL TrySelectListEntry_020c3788(ListView *list, int entryIndex)
{
    u8 state = list->entryStates[entryIndex];
    BOOL selectable = TRUE;

    if (state != 0 && state != 1) {
        selectable = FALSE;
    }
    SelectListEntry_020c3718(list, entryIndex);
    if (!selectable || !func_ov073_020c32a8(list, entryIndex)) {
        return FALSE;
    }
    return TRUE;
}
