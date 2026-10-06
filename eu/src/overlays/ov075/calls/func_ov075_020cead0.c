#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void OpenItemPicker(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void DiscardSelectedItem(void *work);
extern void func_ov075_020ce460(void *work);
extern void SetDialogInputDisabled(void *work);

int func_ov075_020cead0(void *work)
{
    OpenItemPicker(work, DiscardSelectedItem, func_ov075_020ce460, SetDialogInputDisabled);
    return 1;
}
