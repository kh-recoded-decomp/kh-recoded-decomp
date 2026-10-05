#include "nitro/types.h"

extern void OpenSessionArchive_020635b0(int number, int flag);

int OpenDefaultSessionArchive_02069dbc(int context)
{
    OpenSessionArchive_020635b0(0, context + 0xc);
    return 0;
}
