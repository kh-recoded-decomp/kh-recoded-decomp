#include "nitro/types.h"

extern void *gContinueScreenContext;
extern char *func_ov027_020b9a94(char *dst, const char *src);

void func_ov037_020bad44(const char *text)
{
    func_ov027_020b9a94((char *)gContinueScreenContext + 84, text);
}
