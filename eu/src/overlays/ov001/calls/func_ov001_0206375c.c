#include "nitro/types.h"

typedef struct Session {
    u8 pad_000[0x20];
    u32 flags;
    u8 pad_024[0x214 - 0x24];
    u32 modeFlags;
} Session;

extern Session *data_ov001_020a0480;
extern void func_ov001_0206e3d8(void);
extern void func_ov001_0206e444(s32 enable);
extern void SetSubModeFrozen(s32 value);
extern void func_ov001_0207ef44(void);
extern int func_ov001_0206dc38(void);
extern int func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField(int index);
extern void StoreSessionSpawnPoint(int index, int value, u16 field);
extern void ResumeTaskAndClearFlags(void);
extern BOOL IsSessionFlagSet(u32 eventId);
extern void ClearSessionPackedBit(u32 eventId);
extern void ClearStageManagerFlags31IfActive(void);
extern void ClearStageManagerFlags42IfActive(void);
extern void ReleaseSeqArcHeapLevel(int index);
extern int CacheSeqArcStatus(int index);
extern s32 func_ov001_02063a38(void);
extern void QueueAreaSoundArchives(void);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern void func_ov035_020bb354(int stopSeq);
extern int func_02029f5c(void);

void func_ov001_0206375c(void) {
    int index;

    data_ov001_020a0480->flags &= ~0x20;
    func_ov001_0206e3d8();
    func_ov001_0206e444(1);
    SetSubModeFrozen(0);
    func_ov001_0207ef44();
    for (index = 0; index < func_ov001_0206dc38(); index++) {
        StoreSessionSpawnPoint(index, func_ov001_0206dc4c(index), GetBiasAdjustedField(index));
    }
    ResumeTaskAndClearFlags();
    if (!IsSessionFlagSet(0x3528)) {
        ClearStageManagerFlags31IfActive();
        ClearStageManagerFlags42IfActive();
    }
    if (IsSessionFlagSet(0x360c)) {
        ReleaseSeqArcHeapLevel(1);
        ClearSessionPackedBit(0x360c);
        if (func_ov001_02063a38() == 6) {
            func_ov035_020bb354(1);
        } else {
            QueueAreaSoundArchives();
            UpdateEventObjects();
            ForwardToActiveService_02088074();
            CacheSeqArcStatus(2);
        }
    } else {
        ReleaseSeqArcHeapLevel(2);
        if (func_ov001_02063a38() == 6) {
            func_ov035_020bb354(0);
        }
    }
    if (func_02029f5c() == 0) {
        data_ov001_020a0480->modeFlags &= ~0x40000;
    }
}
