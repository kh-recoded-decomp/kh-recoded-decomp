#include "nitro/types.h"

extern int func_ov001_020645c8(u32 id);
extern void func_ov001_02067870(void);
extern void func_ov001_0206daf8(void);
extern void func_ov001_0208804c(void);
extern void QueueSoundCommandForArc_0204d670(int command);
extern void CacheSeqArcStatus_0204e00c(int status);

void func_ov035_020bb334(int stopSeq) {
    if (func_ov001_020645c8(0x360c) == 0) {
        QueueSoundCommandForArc_0204d670(0x1a0);
        func_ov001_0206daf8();
    }
    if (stopSeq != 0) {
        CacheSeqArcStatus_0204e00c(2);
    }
    func_ov001_02067870();
    QueueSoundCommandForArc_0204d670(0x10);
    if (func_ov001_020645c8(0x360c) == 0) {
        func_ov001_0208804c();
    }
}
