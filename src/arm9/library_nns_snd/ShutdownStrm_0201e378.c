#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u32 flags;
    u8 pad_30[0x18];
    u32 alarmNo;
} NNSSndStrm;

extern void func_0201d3d8(u32 alarmNo);
extern void RemoveIntrusiveListObject_020129d8(void *list, void *object);
extern u32 data_0205e17c;

void ShutdownStrm_0201e378(NNSSndStrm *stream)
{
    func_0201d3d8(stream->alarmNo);
    RemoveIntrusiveListObject_020129d8(&data_0205e17c, stream);
    stream->flags = stream->flags & 0xfffffffe;
}
