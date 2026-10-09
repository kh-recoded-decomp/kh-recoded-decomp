#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    int kind;
    u8 pad[0x104];
} PanelModelSlot;

typedef struct {
    u8 pad0[4];
    int selectedSlot;
    u8 pad1[0x118 - 0x8];
    PanelModelSlot slots[8];
    u8 pad2[0xb64 - 0x118 - 8 * 0x108];
    int textBank[3];
    PanelStackEntry stack[6];
    int depth;
    int unk_ba4;
    BOOL hasAvailableItem;
    u8 pad3[0xbbc - 0xbac];
    int mode;
    int confirmFlag;
    int cancelFlag;
    int currentKind;
} PanelScene;

typedef struct {
    u8 pad[0xc];
    int id;
} Widget;

typedef struct {
    int values[3];
} IdTriple;

extern const IdTriple data_ov087_020c7cb8;
extern BOOL func_ov001_020645c8(u32 value);
extern void *func_ov039_020bc1bc(void);
extern BOOL func_ov039_020bc810(void);
extern void InvokeSlotHandlers_020c46e0(PanelScene *scene);
extern void func_ov087_020c4a48(PanelScene *scene);
extern void ShowChoiceWindows_020c4b74(PanelScene *scene, int count);
extern void *func_ov027_020ba2a8(int *bank, int index);
extern void func_ov087_020c4714(PanelScene *scene, int windowIndex, void *text, int color);
extern Widget *func_ov027_020b90f4(void *container);
extern Widget *FindWidgetById_020b90a4(void *container, int id);
extern void SetFocusedWidget_020b96e4(void *container, Widget *widget);
extern void MoveCursorToWidget_020c43c4(PanelScene *scene, Widget *widget, BOOL narrow, BOOL playSound);
extern void SetInfoWindowVisible_020c431c(PanelScene *scene, BOOL visible);
extern void SetEntrySlotsVisible_020b9580(void *container, Widget *widget, BOOL visible);

static inline void FocusWidget(PanelScene *scene, void *container, int id)
{
    Widget *widget = FindWidgetById_020b90a4(container, id);
    SetFocusedWidget_020b96e4(container, widget);
    MoveCursorToWidget_020c43c4(scene, widget, FALSE, FALSE);
}

void RefreshChoiceMenu_020c4d6c(PanelScene *scene, BOOL keepFirst)
{
    int kind = scene->slots[scene->selectedSlot].kind;
    IdTriple ids = data_ov087_020c7cb8;
    BOOL highlighted = FALSE;
    BOOL unlocked = func_ov001_020645c8(0xa12);
    void *container = func_ov039_020bc1bc();
    int count;
    int i;

    InvokeSlotHandlers_020c46e0(scene);
    func_ov087_020c4a48(scene);
    if (kind == scene->currentKind) {
        if (kind == 7 && scene->mode != 3 && scene->mode != 1) {
            if (func_ov039_020bc810() == 0) {
                if (unlocked) {
                    count = 3;
                } else {
                    count = 1;
                }
            } else {
                count = 2;
            }
            ShowChoiceWindows_020c4b74(scene, count);
            if (func_ov039_020bc810() == 0) {
                func_ov087_020c4714(scene, 0, func_ov027_020ba2a8(scene->textBank, 10), 2);
                if (unlocked) {
                    func_ov087_020c4714(scene, 1, func_ov027_020ba2a8(scene->textBank, 0), 2);
                    func_ov087_020c4714(scene, 2, func_ov027_020ba2a8(scene->textBank, 1), 2);
                }
            } else {
                func_ov087_020c4714(scene, 0, func_ov027_020ba2a8(scene->textBank, 0), 2);
                func_ov087_020c4714(scene, 1, func_ov027_020ba2a8(scene->textBank, 1), 2);
            }
            if (func_ov027_020b90f4(container)->id != 2) {
                if (count == 2) {
                    if (func_ov027_020b90f4(container)->id == 4) {
                        FocusWidget(scene, container, 3);
                    } else {
                        SetFocusedWidget_020b96e4(container, func_ov027_020b90f4(container));
                    }
                } else if (count == 1) {
                    FocusWidget(scene, container, 2);
                } else {
                    SetFocusedWidget_020b96e4(container, func_ov027_020b90f4(container));
                }
            } else {
                SetFocusedWidget_020b96e4(container, func_ov027_020b90f4(container));
            }
        } else {
            ShowChoiceWindows_020c4b74(scene, 1);
            func_ov087_020c4714(scene, 0, func_ov027_020ba2a8(scene->textBank, 10), 2);
            FocusWidget(scene, container, 2);
        }
    } else if (kind == 6) {
        ShowChoiceWindows_020c4b74(scene, 2);
        for (i = 0; i < 2; i++) {
            if (i == 0 && !keepFirst) {
                func_ov087_020c4714(scene, i, func_ov027_020ba2a8(scene->textBank, ids.values[i + 1]), 4);
                highlighted = TRUE;
            } else {
                func_ov087_020c4714(scene, i, func_ov027_020ba2a8(scene->textBank, ids.values[i + 1]), 2);
            }
        }
        if (func_ov027_020b90f4(container)->id == 4) {
            FocusWidget(scene, container, 3);
        } else if (highlighted && func_ov027_020b90f4(container)->id == 2) {
            FocusWidget(scene, container, 3);
        } else {
            SetFocusedWidget_020b96e4(container, func_ov027_020b90f4(container));
        }
    } else {
        count = 2;
        if (kind != 3) {
            count = 3;
        }
        ShowChoiceWindows_020c4b74(scene, count);
        for (i = 0; i < count; i++) {
            if (kind != 7 && i == 0 && !keepFirst) {
                func_ov087_020c4714(scene, i, func_ov027_020ba2a8(scene->textBank, ids.values[i]), 4);
                highlighted = TRUE;
            } else {
                func_ov087_020c4714(scene, i, func_ov027_020ba2a8(scene->textBank, ids.values[i]), 2);
            }
        }
        if (kind == 3 && func_ov027_020b90f4(container)->id == 4) {
            FocusWidget(scene, container, 3);
        } else if (highlighted && func_ov027_020b90f4(container)->id == 2) {
            FocusWidget(scene, container, 3);
        } else {
            SetFocusedWidget_020b96e4(container, func_ov027_020b90f4(container));
        }
    }
    if (func_ov027_020b90f4(container)->id == 2) {
        SetInfoWindowVisible_020c431c(scene, scene->hasAvailableItem);
    } else {
        SetInfoWindowVisible_020c431c(scene, FALSE);
    }
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xc), scene->hasAvailableItem);
}
