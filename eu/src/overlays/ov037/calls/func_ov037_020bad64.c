#include "nitro/types.h"

extern void *gContinueScreenContext;
extern char *ClearWidgetTileArea(char *dst, const char *src);

void func_ov037_020bad64(const char *text)
{
    ClearWidgetTileArea((char *)gContinueScreenContext + 84, text);
}
