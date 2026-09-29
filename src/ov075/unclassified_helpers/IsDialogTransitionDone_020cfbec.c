#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x9c38];
    s32 transitionDone : 1;
} DialogWindow;

BOOL IsDialogTransitionDone_020cfbec(DialogWindow *dialog)
{
    return dialog->transitionDone;
}
