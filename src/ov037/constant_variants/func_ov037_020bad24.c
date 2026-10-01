#include "nitro/types.h"

extern void *data_020bb764;
extern char *strcpy_020b9a74(char *dst, const char *src);

void func_ov037_020bad24(const char *text)
{
    strcpy_020b9a74((char *)data_020bb764 + 84, text);
}
