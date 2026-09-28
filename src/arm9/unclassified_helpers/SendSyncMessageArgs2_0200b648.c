#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void *argBuffer;
} SyncObject;

extern BOOL func_0200a930(SyncObject *object, u32 type, BOOL wait);

void SendSyncMessageArgs2_0200b648(SyncObject *object, u32 arg0, u32 arg1) {
    u32 buffer[2];
    object->argBuffer = buffer;
    buffer[0] = arg0;
    buffer[1] = arg1;
    func_0200a930(object, 0xe, 1);
}
