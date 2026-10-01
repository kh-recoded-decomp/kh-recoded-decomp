#include "nitro/types.h"

extern char *data_0206084c;
s32 QueueTypedMessageWithHandle_0202cb24(u16 field1, u16 field2, s32 arg2);
int func_0202c438(void);
void NNS_SndArcStrmStartPrepared_0202029c(void *handle);

BOOL PrepareAndStartStream_0204dd4c(int streamIndex, int streamId)
{
    u8 status;
    *(u8 *)(data_0206084c + 0xb47d8) = streamId;
    status = 0;
    QueueTypedMessageWithHandle_0202cb24(streamIndex, streamId, (s32)&status);
    func_0202c438();
    /* Status 3 means preparation failed */
    if (status == 3)
        return FALSE;
    NNS_SndArcStrmStartPrepared_0202029c(data_0206084c + 0xb44c0 + streamIndex * 4);
    return TRUE;
}

