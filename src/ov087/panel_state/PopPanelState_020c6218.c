#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb70];
    PanelStackEntry stack[6];
    int depth;
} PanelScene;

typedef struct {
    u8 pad_000[0x214];
    u32 unk_bits : 13;
    u32 cancelAllowed : 1;
} SessionState;

extern SessionState *data_ov001_020a0460;
extern void *func_ov039_020bc1bc(void);
extern BOOL func_ov039_020bc810(void);
extern void PopStackEntry_020bc8a0(void);
extern void func_ov039_020bbf78(int a, int b, int c);
extern void ClearSessionFlagsWord_02064d70(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL UpdateEntryCountRecord_020c42a0(PanelScene *scene);
extern void PushPanelState_020c61b0(PanelScene *scene, int stateId);
extern void EnterPanelState_020c6118(PanelScene *scene, int stateId, int previousState);
extern void SetFocusedWidget_020b96e4(void *container, void *element);
extern void MoveCursorToWidget_020c43c4(PanelScene *scene, void *element, BOOL narrow, BOOL playSound);
extern void *FindWidgetById_020b90a4(void *container, int elementId);
extern void SetEntrySlotsVisible_020b9580(void *container, void *element, BOOL visible);

void PopPanelState_020c6218(PanelScene *scene, int soundIndex)
{
    void *container = func_ov039_020bc1bc();
    int depth = scene->depth;
    void *focusElement;
    int previousState;
    int sound = 3;

    if (soundIndex >= 0) {
        sound = soundIndex;
    }
    if (depth == 0) {
        if (!func_ov039_020bc810()) {
            if (!data_ov001_020a0460->cancelAllowed) {
                return;
            }
            ClearSessionFlagsWord_02064d70();
            func_ov039_020bbf78(-1, -1, 1);
            PlaySoundEffect_0204d924(0, sound);
            return;
        }
        PopStackEntry_020bc8a0();
        func_ov039_020bbf78(0, -1, 1);
        PlaySoundEffect_0204d924(0, sound);
        return;
    }
    previousState = scene->stack[depth].stateId;
    focusElement = scene->stack[depth].focusElement;
    scene->depth = depth - 1;
    if ((u32)(previousState - 0x10) <= 1) {
        if (soundIndex < 0) {
            sound = 7;
        }
        if (UpdateEntryCountRecord_020c42a0(scene)) {
            PushPanelState_020c61b0(scene, 0x11);
            PlaySoundEffect_0204d924(0, sound);
            return;
        }
    }
    EnterPanelState_020c6118(scene, scene->stack[scene->depth].stateId, previousState);
    if (focusElement != NULL) {
        SetFocusedWidget_020b96e4(func_ov039_020bc1bc(), focusElement);
        MoveCursorToWidget_020c43c4(scene, focusElement, FALSE, FALSE);
    }
    PlaySoundEffect_0204d924(0, sound);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0), TRUE);
}
