#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void ItemList_OpenConfirmWindow(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void ItemList_ReleaseCursorEntry(void *work);
extern void ItemScreen_DrawItemPrompt(void *work);
extern void SetDialogInputDisabled_020ca3a8(void *work);

int func_ov076_020ca8e0(void *work)
{
    ItemList_OpenConfirmWindow(work, ItemList_ReleaseCursorEntry, ItemScreen_DrawItemPrompt, SetDialogInputDisabled_020ca3a8);
    return 1;
}
