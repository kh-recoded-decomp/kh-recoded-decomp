#include "nitro/types.h"

typedef struct BgmState {
    s8 mode;
    u8 track;
    u16 timer;
    s8 override;
    u8 pad_05[0xb];
    s8 kind;
} BgmState;

typedef struct FieldSession {
    u8 pad_0000[0x214];
    u32 unk0 : 7;
    u32 bgmLocked : 1;
    u8 pad_0218[0x25e0];
    BgmState bgm;
} FieldSession;

extern FieldSession *data_ov001_020a0480;
extern int func_ov001_02067ed4(void);
extern BOOL IsSessionFlagSet(u32 value);
extern BOOL IsEntryFlag2Active(int index);
extern int func_0204d8cc(int track, int fade);
extern int IsFieldTrackFlagSet(void);
extern BOOL IsSceneState4(void);
extern u8 func_ov001_02068094(int index);
extern u8 func_ov001_020680b0(int index);

void UpdateFieldBgm(FieldSession *session) {
    BgmState *bgm = &session->bgm;
    int battle = 0;
    int area = func_ov001_02067ed4();
    BOOL change;

    if (session->bgmLocked) {
        return;
    }
    if (IsSessionFlagSet(0x3308)) {
        return;
    }
    if (area < 0) {
        return;
    }
    if (session->bgm.kind == 6) {
        return;
    }
    if (IsEntryFlag2Active(0)) {
        return;
    }
    if (data_ov001_020a0480->bgm.override != -1 && bgm->track != 0x27) {
        bgm->track = 0x27;
        func_0204d8cc(bgm->track, 30);
    }
    if (session->bgm.kind != 4 && session->bgm.kind != 7) {
        battle = IsFieldTrackFlagSet();
    }
    if (data_ov001_020a0480->bgm.override != -1) {
        s8 mode = 1;
        if (battle == 0) {
            mode = 2;
        }
        bgm->mode = mode;
        return;
    }
    if (battle != 0) {
        if (IsSceneState4()) {
            return;
        }
        bgm->timer = 0;
        bgm->track = func_ov001_020680b0(func_ov001_02067ed4());
        func_0204d8cc(bgm->track, 30);
        bgm->mode = 1;
        return;
    }
    change = FALSE;
    if (bgm->mode == 0) {
        change = TRUE;
    } else if (bgm->mode == 1) {
        if (bgm->timer >= 90) {
            change = TRUE;
        } else {
            bgm->timer++;
        }
    } else if (bgm->track != func_ov001_02068094(func_ov001_02067ed4())) {
        change = TRUE;
    }
    if (change) {
        bgm->track = func_ov001_02068094(func_ov001_02067ed4());
        func_0204d8cc(bgm->track, 30);
        bgm->mode = 2;
    }
}
