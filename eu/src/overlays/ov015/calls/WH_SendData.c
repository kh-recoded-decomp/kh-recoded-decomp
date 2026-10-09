#include "nitro/types.h"

typedef void (*WhSendCallback)(BOOL delivered);

extern BOOL WH_StateInSetMPData(void *data, u16 dataSize, WhSendCallback callback);

BOOL WH_SendData(void *data, u16 dataSize, WhSendCallback callback)
{
    return WH_StateInSetMPData(data, dataSize, callback);
}
