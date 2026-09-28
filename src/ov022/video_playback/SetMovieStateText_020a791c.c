#include "nitro/types.h"

extern void *data_020b7d80;
extern char *strcpy_02021e60(char *dst, const char *src);

void SetMovieStateText_020a791c(const char *text)
{
    strcpy_02021e60((char *)data_020b7d80 + 0x8c0, text);
}
