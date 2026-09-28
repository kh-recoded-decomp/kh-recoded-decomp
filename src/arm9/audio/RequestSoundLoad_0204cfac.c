#include "nitro/types.h"
#include "nnsys/snd.h"

extern u8 *g_soundWork_0206084c;
extern void func_0201f030(NNSSndHeapHandle heap);
extern void QueueTypedMessage_0202ca88(u16 messageId, int arg1, int arg2);

void RequestSoundLoad_0204cfac(u32 soundId)
{
    u8 *base = g_soundWork_0206084c;

    *(u8 *)(base + 0xb472e) = 1;
    *(u16 *)(base + 0xb472a) = (u16)soundId;
    func_0201f030(*(NNSSndHeapHandle *)(base + 0xb04b8));
    QueueTypedMessage_0202ca88((u16)soundId, *(int *)(base + 0xb04b8), (int)(base + 0xb472e));
}
