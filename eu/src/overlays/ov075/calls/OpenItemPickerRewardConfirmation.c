#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void OpenItemPicker(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void ConsumeItemPickerSelectionAndApplyReward(void *work);
extern void DrawSelectedEntryName(void *work);
extern void SetDialogInputDisabled(void *work);

int OpenItemPickerRewardConfirmation(void *work)
{
    OpenItemPicker(work, ConsumeItemPickerSelectionAndApplyReward, DrawSelectedEntryName, SetDialogInputDisabled);
    return 1;
}
