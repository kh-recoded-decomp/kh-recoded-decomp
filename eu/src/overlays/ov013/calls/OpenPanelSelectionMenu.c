#include "src/overlays/ov013/Ov013PanelState.h"

extern void RefreshProgressCaption(void);
extern void DrawPanelResultCaption(int mode);
extern PanelWidget *FindWidgetById(void *root, int id);
extern void SetFocusedWidget(void *root, PanelWidget *widget);
extern int DispatchContextCommand(int command, int arg1, int arg2, int arg3);
extern void PlaySoundEffect(int id, int flag);
extern void func_ov013_02070e40(s32 useAlt);
extern void func_ov013_02070a50(void);
extern void SetEntrySlotsVisible(int root, int *widget, int visible);
extern void func_ov027_020b9604(int root, int *widget);
struct Ov008SubitemBlock;
extern void ApplySelectedSubitemValues(int root, struct Ov008SubitemBlock *widget, int useAlt);
extern void func_ov027_020b90b8(void *root, u32 callback);
extern void func_ov013_02074420(int context);
extern void func_ov027_020b96c0(int root, int widget, int mode);

void OpenPanelSelectionMenu(void)
{
    Ov013PanelState *state;
    u8 *root;

    gOv013PanelState->flags |= 8;
    RefreshProgressCaption();
    DrawPanelResultCaption(2);
    SetFocusedWidget(gOv013PanelState->widgets,
                     FindWidgetById(gOv013PanelState->widgets, 10));
    gOv013PanelState->selectedWidget = FindWidgetById(gOv013PanelState->widgets, 10)->id;

    state = gOv013PanelState;
    if (DispatchContextCommand(7, 0, 0, 0) < state->list.cursor) {
        PlaySoundEffect(2, 5);
        ChangePanelMenuState(1);
        return;
    }
    state->resultMode = 0;
    func_ov013_02070e40(0);
    func_ov013_02070a50();

    SetEntrySlotsVisible((int)gOv013PanelState->widgets,
                        (int *)FindWidgetById(gOv013PanelState->widgets, 9), 1);
    SetEntrySlotsVisible((int)gOv013PanelState->widgets,
                        (int *)FindWidgetById(gOv013PanelState->widgets, 10), 1);
    func_ov027_020b9604((int)gOv013PanelState->widgets,
                      (int *)FindWidgetById(gOv013PanelState->widgets, 0));
    func_ov027_020b9604((int)gOv013PanelState->widgets,
                      (int *)FindWidgetById(gOv013PanelState->widgets, 2));
    func_ov027_020b9604((int)gOv013PanelState->widgets,
                      (int *)FindWidgetById(gOv013PanelState->widgets, 3));
    root = gOv013PanelState->widgets;
    ApplySelectedSubitemValues((int)root, (struct Ov008SubitemBlock *)FindWidgetById(root, 2), 0);
    root = gOv013PanelState->widgets;
    ApplySelectedSubitemValues((int)root, (struct Ov008SubitemBlock *)FindWidgetById(root, 3), 0);
    func_ov027_020b90b8(gOv013PanelState->widgets, (u32)func_ov013_02074420);
    PlaySoundEffect(2, 1);
    root = gOv013PanelState->widgets;
    func_ov027_020b9604((int)root, (int *)FindWidgetById(root, 5));
    root = gOv013PanelState->widgets;
    func_ov027_020b96c0((int)root, (int)FindWidgetById(root, 5), 0);
    gOv013PanelState->step = 0;
}
