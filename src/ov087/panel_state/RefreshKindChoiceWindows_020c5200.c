#pragma opt_propagation off
#include "nitro/types.h"

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
    int textBank[0x11];
    BOOL hasAvailableItem;
    u8 pad3[0xbc8 - 0xbac];
    int currentKind;
    int alternateKind;
} PanelScene;

typedef struct {
    u8 pad[0xc];
    int id;
} Widget;

extern BOOL func_ov001_020645c8(u32 value);
extern void *func_ov039_020bc1bc(void);
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
extern void RefreshChoiceMenu_020c4d6c(PanelScene *scene, BOOL keepFirst);

void RefreshKindChoiceWindows_020c5200(PanelScene *scene)
{
    int textId = 0;
    void *container = func_ov039_020bc1bc();
    int kind = scene->slots[scene->selectedSlot].kind;
    Widget *widget;

    InvokeSlotHandlers_020c46e0(scene);
    func_ov087_020c4a48(scene);
    if (kind == scene->currentKind) {
        if (kind == 7 && func_ov001_020645c8(0xa12)) {
            ShowChoiceWindows_020c4b74(scene, 3);
            func_ov087_020c4714(scene, 0, func_ov027_020ba2a8(scene->textBank, 8), 2);
            if (scene->alternateKind == 7) {
                textId = 7;
            }
            func_ov087_020c4714(scene, 1, func_ov027_020ba2a8(scene->textBank, textId), 2);
            func_ov087_020c4714(scene, 2, func_ov027_020ba2a8(scene->textBank, 1), 2);
            widget = FindWidgetById_020b90a4(container, 2);
            SetFocusedWidget_020b96e4(container, widget);
            MoveCursorToWidget_020c43c4(scene, widget, FALSE, FALSE);
        } else {
            ShowChoiceWindows_020c4b74(scene, 1);
            func_ov087_020c4714(scene, textId, func_ov027_020ba2a8(scene->textBank, 8), 2);
            widget = FindWidgetById_020b90a4(container, 2);
            SetFocusedWidget_020b96e4(container, widget);
            MoveCursorToWidget_020c43c4(scene, widget, textId, textId);
        }
        if (func_ov027_020b90f4(container)->id == 2) {
            SetInfoWindowVisible_020c431c(scene, scene->hasAvailableItem);
        } else {
            SetInfoWindowVisible_020c431c(scene, FALSE);
        }
        SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xc), scene->hasAvailableItem);
    } else if (kind == scene->alternateKind) {
        ShowChoiceWindows_020c4b74(scene, 1);
        func_ov087_020c4714(scene, textId, func_ov027_020ba2a8(scene->textBank, 7), 2);
        widget = FindWidgetById_020b90a4(container, 2);
        SetFocusedWidget_020b96e4(container, widget);
        MoveCursorToWidget_020c43c4(scene, widget, textId, textId);
        if (func_ov027_020b90f4(container)->id == 2) {
            SetInfoWindowVisible_020c431c(scene, scene->hasAvailableItem);
        } else {
            SetInfoWindowVisible_020c431c(scene, textId);
        }
        SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xc), scene->hasAvailableItem);
    } else {
        RefreshChoiceMenu_020c4d6c(scene, TRUE);
    }
}
