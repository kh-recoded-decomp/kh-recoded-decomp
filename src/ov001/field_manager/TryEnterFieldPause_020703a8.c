#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x42c];
    s32 lockCount;
    u8 pad_430[0x47c - 0x430];
    s32 busy;
    u32 isSliding : 1;
    u32 unk_480_1 : 2;
    u32 resumePending : 1;
    u32 isPaused : 1;
    u32 menuRequested : 1;
    u32 unk_480_6 : 8;
    u32 alternateWidgets : 1;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern u32 func_ov001_02064490(void);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsSceneModeThreeOrSix_0207b60c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsHudFlag9Set_02072884(void);
extern BOOL IsSessionIdle_02063860(void);
extern int func_0202c438(void);
extern void OpenFieldMenuMode_020641d4(u32 kind);
extern void SelectActiveEntry_020011a4(int index);
extern void SuspendFieldForPause_02071270(void);
extern BOOL CanOpenFieldMenu_020735d8(void);
extern u32 func_ov001_0207b3cc(void);
extern void SetAlternateMenuWidgets_020b61f4(int enabled);
extern u32 func_02028958(u32 mode);
extern BOOL OpenPanel_020285a0(int panel);

BOOL TryEnterFieldPause_020703a8(int panel)
{
    if (data_ov001_020a04a4.manager->isPaused == 1) {
        return TRUE;
    }
    if (data_ov001_020a04a4.manager->lockCount != 0) {
        return FALSE;
    }
    if (func_ov001_02064490()) {
        if (data_ov001_020a04a4.manager->isPaused == 1) {
            return TRUE;
        }
        return FALSE;
    }
    if (func_ov001_020645c8(0x363e)) {
        return FALSE;
    }
    if (!IsSceneModeThreeOrSix_0207b60c()) {
        return FALSE;
    }
    if (!IsHudFlag7Set_020725bc() && !IsFieldFlag10Set_020728c4() && !IsHudFlag9Set_02072884() && data_ov001_020a04a4.manager->busy == 0) {
        if (IsSessionIdle_02063860()) {
            func_0202c438();
            OpenFieldMenuMode_020641d4(7);
            data_ov001_020a04a4.manager->menuRequested = 1;
            data_ov001_020a04a4.manager->resumePending = 1;
            return FALSE;
        }
        data_ov001_020a04a4.manager->isPaused = 1;
        SelectActiveEntry_020011a4(1);
        SuspendFieldForPause_02071270();
        if (CanOpenFieldMenu_020735d8() && func_ov001_0207b3cc() == 2) {
            SetAlternateMenuWidgets_020b61f4(1);
            data_ov001_020a04a4.manager->alternateWidgets = 1;
            func_02028958(0);
        }
        OpenPanel_020285a0(panel);
    } else {
        data_ov001_020a04a4.manager->isPaused = 1;
        SelectActiveEntry_020011a4(1);
        SuspendFieldForPause_02071270();
        OpenPanel_020285a0(panel);
        data_ov001_020a04a4.manager->resumePending = 0;
    }
    return TRUE;
}
