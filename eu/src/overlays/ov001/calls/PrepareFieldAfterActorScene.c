#include "nitro/types.h"

typedef struct Session {
    u8 pad_000[0x20];
    u32 flags;
    u8 pad_024[0x214 - 0x24];
    u32 modeFlags;
} Session;

extern Session *gFieldSessionWork;
extern void DeactivateManagerEntries(void);
extern void SetFieldEntriesPaused(s32 enable);
extern void SetSubModeFrozen(s32 value);
extern void RefreshFieldObjectsAndEntryActorSlots(void);
extern int GetManagedActorCount(void);
extern int GetManagedActorPosition(int index);
extern u16 GetBiasAdjustedField(int index);
extern void StoreSessionSpawnPoint(int index, int value, u16 field);
extern void ResumeTaskAndClearFlags(void);
extern BOOL IsSessionFlagSet(u32 eventId);
extern void ClearSessionPackedBit(u32 eventId);
extern void ClearStageManagerFlags31IfActive(void);
extern void ClearStageManagerFlags42IfActive(void);
extern void ReleaseSeqArcHeapLevel(int index);
extern int CacheSeqArcStatus(int index);
extern s32 GetFieldSessionState(void);
extern void QueueAreaSoundArchives(void);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern void QueueAreaSceneSoundState(int stopSeq);
extern int GetMainBrightnessSetting(void);

void PrepareFieldAfterActorScene(void) {
    int index;

    gFieldSessionWork->flags &= ~0x20;
    DeactivateManagerEntries();
    SetFieldEntriesPaused(1);
    SetSubModeFrozen(0);
    RefreshFieldObjectsAndEntryActorSlots();
    for (index = 0; index < GetManagedActorCount(); index++) {
        StoreSessionSpawnPoint(index, GetManagedActorPosition(index), GetBiasAdjustedField(index));
    }
    ResumeTaskAndClearFlags();
    if (!IsSessionFlagSet(0x3528)) {
        ClearStageManagerFlags31IfActive();
        ClearStageManagerFlags42IfActive();
    }
    if (IsSessionFlagSet(0x360c)) {
        ReleaseSeqArcHeapLevel(1);
        ClearSessionPackedBit(0x360c);
        if (GetFieldSessionState() == 6) {
            QueueAreaSceneSoundState(1);
        } else {
            QueueAreaSoundArchives();
            UpdateEventObjects();
            ForwardToActiveService_02088074();
            CacheSeqArcStatus(2);
        }
    } else {
        ReleaseSeqArcHeapLevel(2);
        if (GetFieldSessionState() == 6) {
            QueueAreaSceneSoundState(0);
        }
    }
    if (GetMainBrightnessSetting() == 0) {
        gFieldSessionWork->modeFlags &= ~0x40000;
    }
}
