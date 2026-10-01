#include "nitro/types.h"

extern void *data_020bb764;
extern char *strcpy_020b9b94(char *dst, const char *src);

void func_ov037_020bad44(const char *text)
{
    strcpy_020b9b94((char *)data_020bb764 + 84, text);
}
