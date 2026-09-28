#include "nitro/types.h"
#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

char * STD_CopyString_02010ba4 (char * destp, const char * srcp)
{
    char * retval = destp;

    while (*srcp) {
        *destp++ = (char)*srcp++;
    }

    *destp = '\0';

    return retval;
}
