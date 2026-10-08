#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void OpenItemPicker(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void func_ov075_020ce908(void *work);
extern void DrawSelectedEntryName(void *work);
extern void SetDialogInputDisabled(void *work);

int func_ov075_020ceaec(void *work)
{
    OpenItemPicker(work, func_ov075_020ce908, DrawSelectedEntryName, SetDialogInputDisabled);
    return 1;
}
