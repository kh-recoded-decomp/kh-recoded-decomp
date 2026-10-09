#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 model[0x104];
} ListEntry;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    int step;
    int cursor;
    int entryCount;
    u8 pad_00c[0x10c];
    ListEntry entries[8];
    u8 pad_958[0x218];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0xc];
    BOOL brightened;
    u8 pad_bb4[0x8];
    int mode;
    u8 pad_bc0[0x8];
    int lockedId;
    int secondId;
    int thirdId;
} PanelScene;

typedef struct {
    u32 low : 13;
    u32 menuLocked : 1;
    u32 unk_14 : 2;
    u32 menuMode : 2;
    u32 high : 14;
} SessionFlags;

typedef struct {
    u8 pad_000[0x214];
    SessionFlags flags;
} Session;

extern Session *data_ov001_020a0460;

extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL func_ov039_020bc810(void);
extern void func_ov087_020c6378(void);
extern void SetSelectionIfChanged_020bc92c(int id);
extern void AcquireRecordSlot_02051d3c(int slot, int arg);
extern void func_ov087_020c6ab0(PanelScene *scene, int id);
extern void LoadPanelBackground_020c6590(PanelScene *scene);
extern void func_ov087_020c69a4(PanelScene *scene);
extern void InitPanelTextLayers_020c663c(PanelScene *scene);
extern void func_ov087_020c5758(PanelScene *scene, int arg);
extern void FocusElementForState_020c5860(PanelScene *scene, int stateId);
extern void func_ov087_020c5964(PanelScene *scene, int arg);
extern void *func_ov039_020bc1bc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern BOOL func_ov087_020c44a4(PanelScene *scene, void *widget);
extern BOOL UpdateEntryCountRecord_020c42a0(PanelScene *scene);
extern void PushPanelState_020c61b0(PanelScene *scene, int stateId);
extern int func_0204d8b8(int arg0, int arg1);
extern void SelectRecordPage_020c2060(int pageIndex);

int InitPanelScene_020c713c(PanelScene *scene)
{
    int result;
    int bonusMode;
    int lockedId;
    int count;
    int i;
    u32 menuMode;

    scene->brightened = TRUE;
    result = 0;
    if (scene->step == 0) {
        scene->lockedId = ReadGlobalPackedBits_02027348(0x330b, 10) / 100 - 1;
        scene->secondId = ReadGlobalPackedBits_02027348(0x420b, 10) / 100 - 1;
        scene->thirdId = ReadGlobalPackedBits_02027348(0x510b, 10) / 100 - 1;
        bonusMode = ReadSessionPackedBits_02064574(0x1a00, 2);
        if (!func_ov039_020bc810()) {
            if (data_ov001_020a0460->flags.menuLocked) {
                scene->mode = 0;
            } else {
                menuMode = data_ov001_020a0460->flags.menuMode;
                if (menuMode == 1) {
                    scene->mode = bonusMode;
                } else {
                    scene->mode = menuMode;
                }
            }
        } else {
            scene->mode = bonusMode;
        }
        func_ov087_020c6378();
        SetSelectionIfChanged_020bc92c(6);
        AcquireRecordSlot_02051d3c(2, 0);
        lockedId = scene->lockedId;
        if ((u32)(lockedId - 5) <= 1) {
            scene->entryCount = 5;
        } else if (lockedId == 7 && func_ov001_020645c8(0xa12)) {
            scene->entryCount = 8;
        } else {
            scene->entryCount = lockedId;
        }
        if (scene->mode != 0 || !func_ov039_020bc810()) {
            count = scene->entryCount + 1;
            if (count >= 8) {
                count = 8;
            }
            scene->entryCount = count;
            func_ov087_020c6ab0(scene, scene->lockedId);
            for (i = 0; i < scene->entryCount; i++) {
                if (scene->lockedId == scene->entries[i].id) {
                    scene->cursor = i;
                    break;
                }
            }
        } else {
            scene->cursor = 0;
            func_ov087_020c6ab0(scene, -1);
        }
        LoadPanelBackground_020c6590(scene);
        func_ov087_020c69a4(scene);
        InitPanelTextLayers_020c663c(scene);
        switch (scene->mode) {
        case 0:
            scene->stack[0].stateId = 1;
            func_ov087_020c5758(scene, 0);
            break;
        case 1:
            scene->stack[0].stateId = 2;
            FocusElementForState_020c5860(scene, 0);
            break;
        case 2:
            scene->stack[0].stateId = 3;
            func_ov087_020c5964(scene, 0);
            break;
        }
        scene->stack[0].focusElement = NULL;
        if (!func_ov087_020c44a4(scene, FindWidgetById_020b90a4(func_ov039_020bc1bc(), 2)) &&
            UpdateEntryCountRecord_020c42a0(scene)) {
            PushPanelState_020c61b0(scene, 0x11);
        }
    } else {
        func_0204d8b8(result, 10);
        SelectRecordPage_020c2060(scene->entries[scene->cursor].id);
        result = 1;
    }
    scene->step++;
    return result;
}
