#include "nitro/types.h"

extern void *gContinueScreenContext;
extern char *BlitWidgetToTileTable(char *dst, const char *src);

void func_ov037_020bad44(const char *text)
{
    BlitWidgetToTileTable((char *)gContinueScreenContext + 84, text);
}
