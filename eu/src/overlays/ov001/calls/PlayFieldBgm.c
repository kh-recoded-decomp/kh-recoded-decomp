#include "nitro/types.h"

#define GetCurrentFieldAreaIndex func_ov001_02067ed4
#define GetAreaNormalBgm func_ov001_02068094
#define GetAreaBattleBgm func_ov001_020680b0
#define QueueBgmTrackChange func_0204d8cc

typedef struct FieldBgmState {
    s8 mode;
    u8 track;
} FieldBgmState;

typedef struct FieldSession {
    u8 unknown00[0x27f8];
    FieldBgmState bgm;
} FieldSession;

enum { FIELD_BGM_NORMAL = 2 };

extern FieldSession *data_ov001_020a0480;
extern int GetCurrentFieldAreaIndex(void);
extern u8 GetAreaNormalBgm(int areaIndex);
extern u8 GetAreaBattleBgm(int areaIndex);
extern int QueueBgmTrackChange(int track, int fadeFrames);
extern u32 SetScriptBusyFlag(u32 value);

void PlayFieldBgm(BOOL useBattleTrack, int fadeFrames)
{
    FieldBgmState *bgm = &data_ov001_020a0480->bgm;

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
    SetScriptBusyFlag(~0U);
}
