#include "nitro/types.h"

extern char data_ov001_0209eb04[];
extern void OpenSessionArchive(int number, int flag);

int OpenNamedSessionArchive(int context)
{
    OpenSessionArchive((int)data_ov001_0209eb04, context + 0xc);
    return 0;
}
