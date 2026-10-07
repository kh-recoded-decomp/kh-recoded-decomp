#include "nitro/types.h"

extern int IsSessionFlagSet(u32 id);
extern void QueueAreaSoundArchives(void);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern void QueueSoundCommandForArc(int command);
extern void CacheSeqArcStatus(int status);

void func_ov035_020bb354(int stopSeq) {
    if (IsSessionFlagSet(0x360c) == 0) {
        QueueSoundCommandForArc(0x1a0);
        UpdateEventObjects();
    }
    if (stopSeq != 0) {
        CacheSeqArcStatus(2);
    }
    QueueAreaSoundArchives();
    QueueSoundCommandForArc(0x10);
    if (IsSessionFlagSet(0x360c) == 0) {
        ForwardToActiveService_02088074();
    }
}
