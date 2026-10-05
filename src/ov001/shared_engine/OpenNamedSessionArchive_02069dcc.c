#include "nitro/types.h"

extern char data_ov001_0209eae4[];
extern void OpenSessionArchive_020635b0(int number, int flag);

int OpenNamedSessionArchive_02069dcc(int context)
{
    OpenSessionArchive_020635b0((int)data_ov001_0209eae4, context + 0xc);
    return 0;
}
