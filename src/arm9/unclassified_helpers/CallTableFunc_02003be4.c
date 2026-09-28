#include "nitro/types.h"

typedef void (*TableFunc)(void *arg);

extern TableFunc data_02055bd8[];

void CallTableFunc_02003be4(int index, void *arg)
{
    data_02055bd8[index](arg);
}
