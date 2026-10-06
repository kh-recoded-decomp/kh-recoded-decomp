#include "nitro/types.h"

extern void OpenSessionArchive(int number, int flag);

int OpenDefaultSessionArchive(int context)
{
    OpenSessionArchive(0, context + 0xc);
    return 0;
}
