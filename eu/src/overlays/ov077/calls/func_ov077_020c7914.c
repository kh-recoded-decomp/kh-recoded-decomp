#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void OpenItemConfirmWindow(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void ItemList_ReleaseCursorEntry_020c73ec(void *work);
extern void DrawItemNameHeader(void *work);
extern void SetDialogInputDisabled_020c73dc(void *work);

int func_ov077_020c7914(void *work)
{
    OpenItemConfirmWindow(work, ItemList_ReleaseCursorEntry_020c73ec, DrawItemNameHeader, SetDialogInputDisabled_020c73dc);
    return 1;
}
