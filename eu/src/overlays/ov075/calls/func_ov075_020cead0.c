#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void OpenItemPicker(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void DiscardSelectedItem(void *work);
extern void DrawItemPickerHeader(void *work);
extern void SetDialogInputDisabled(void *work);

int func_ov075_020cead0(void *work)
{
    OpenItemPicker(work, DiscardSelectedItem, DrawItemPickerHeader, SetDialogInputDisabled);
    return 1;
}
