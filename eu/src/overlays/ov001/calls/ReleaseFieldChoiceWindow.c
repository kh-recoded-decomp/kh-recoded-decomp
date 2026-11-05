#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);

void ReleaseFieldChoiceWindow(u32 context)
{
    DestroyFndObjectList(context + 0x1fc);
}
