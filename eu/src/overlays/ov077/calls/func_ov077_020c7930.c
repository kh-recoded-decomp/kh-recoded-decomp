#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void OpenItemConfirmWindow(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void ItemList_ReturnCursorItem_020c774c(void *work);
extern void DrawItemNameUseHeader(void *work);
extern void SetDialogInputDisabled_020c73dc(void *work);

int func_ov077_020c7930(void *work)
{
    OpenItemConfirmWindow(work, ItemList_ReturnCursorItem_020c774c, DrawItemNameUseHeader, SetDialogInputDisabled_020c73dc);
    return 1;
}
