#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void ItemList_OpenConfirmWindow(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void ItemList_ReturnCursorItem(void *work);
extern void ItemList_DrawSelectedName(void *work);
extern void SetDialogInputDisabled_020ca3a8(void *work);

int OpenSlotMenuRewardConfirmation(void *work)
{
    ItemList_OpenConfirmWindow(work, ItemList_ReturnCursorItem, ItemList_DrawSelectedName, SetDialogInputDisabled_020ca3a8);
    return 1;
}
