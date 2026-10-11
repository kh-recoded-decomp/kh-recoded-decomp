#include "nitro/types.h"

extern char gSessionArchiveName[];
extern void OpenSessionArchive(int number, int flag);

int OpenNamedSessionArchive(int context)
{
    OpenSessionArchive((int)gSessionArchiveName, context + 0xc);
    return 0;
}
