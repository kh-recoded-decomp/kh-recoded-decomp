#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern u32 func_0202cacc(u16 a, u16 b, u32 c, void *arg);
extern void func_0202c438(void);
extern u32 func_0201ecbc(u32 seqArcNo);
extern void func_0201ee80(u32 seqArcNo, u32 index);

void QueueSoundCommandForArc_0204d670(u32 seqArcNo, u32 unused2, u32 unused3, u32 commandArg)
{
    u32 count;
    u32 i = 0;
    u8 flagBuf[4];
    u32 valueBuf;

    flagBuf[0] = 0;
    valueBuf = commandArg;
    func_0202cacc((u16)(seqArcNo & 0xffff), (u16)((seqArcNo + 0x29) & 0xffff),
                  *(u32 *)(g_soundWork_0206084c + 0xb04b4), flagBuf);
    func_0202c438();
    count = func_0201ecbc(seqArcNo);
    if (count != 0) {
        do {
            func_0201ee80(seqArcNo, i);
            i = i + 1;
        } while (i < count);
    }
}
