#include "nitro/types.h"

#define GetCurrentFieldAreaIndex GetCurrentSceneEntryIndex
#define GetAreaNormalBgm GetSceneEntryPrimaryBgmId
#define GetAreaBattleBgm GetSceneEntrySecondaryBgmId
#define QueueBgmTrackChange QueueSoundKind4

typedef struct FieldBgmState {
    s8 mode;
    u8 track;
} FieldBgmState;

typedef struct FieldSession {
    u8 unknown00[0x27f8];
    FieldBgmState bgm;
} FieldSession;

enum { FIELD_BGM_NORMAL = 2 };

extern FieldSession *gFieldSessionWork;
extern int GetCurrentFieldAreaIndex(void);
extern u8 GetAreaNormalBgm(int areaIndex);
extern u8 GetAreaBattleBgm(int areaIndex);
extern int QueueBgmTrackChange(int track, int fadeFrames);
extern u32 SetScriptBgmSelection(u32 value);

void PlayFieldBgm(BOOL useBattleTrack, int fadeFrames)
{
    FieldBgmState *bgm = &gFieldSessionWork->bgm;

    if (useBattleTrack) {
        bgm->track = GetAreaBattleBgm(GetCurrentFieldAreaIndex());
        if (fadeFrames < 0) {
            fadeFrames = 30;
        }
        QueueBgmTrackChange(bgm->track, fadeFrames);
        bgm->mode = FIELD_BGM_NORMAL;
    } else {
        bgm->track = GetAreaNormalBgm(GetCurrentFieldAreaIndex());
        if (fadeFrames < 0) {
            fadeFrames = 30;
        }
        QueueBgmTrackChange(bgm->track, fadeFrames);
        bgm->mode = FIELD_BGM_NORMAL;
    }
    SetScriptBgmSelection(~0U);
}
