#include "nitro/types.h"
#include "src/overlays/ov001/FieldTextFormats.h"

extern u32 gSubscenePanelWork;

u8 *GetSubsceneTextOrEmpty(void)
{
    u8 *data;

    if ((gSubscenePanelWork == 0) ||
        (data = *(u8 **)(gSubscenePanelWork + 0x18), data == (u8 *)0x0)) {
        data = (u8 *)gFieldTextFormats.empty;
    }
    return data;
}
