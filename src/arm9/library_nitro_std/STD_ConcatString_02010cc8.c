#include "nitro/types.h"

extern int func_02010c74(const char *str);
extern char *STD_CopyString_02010ba4(char *dst, const char *src);

char *STD_ConcatString_02010cc8(char *dst, const char *src)
{
    int len = func_02010c74(dst);

    STD_CopyString_02010ba4(dst + len, src);
    return dst;
}
