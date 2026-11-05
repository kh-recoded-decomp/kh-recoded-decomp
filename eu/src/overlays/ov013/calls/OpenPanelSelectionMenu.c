#include "src/overlays/ov027/WidgetRecordOps.h"
#include "src/overlays/ov013/Ov013PanelState.h"

extern void RefreshProgressCaption(void);
extern void DrawPanelResultCaption(int mode);
extern PanelWidget *FindWidgetById(void *root, int id);
extern void SetFocusedWidget(void *root, PanelWidget *widget);
extern int DispatchContextCommand(int command, int arg1, int arg2, int arg3);
extern void PlaySoundEffect(int id, int flag);
extern void ApplyOv013SubitemValuesToWidgets(s32 useAlt);
extern void UploadOv013SubBg0ScreenEntry1(void);
extern void SetEntrySlotsVisible(int root, int *widget, int visible);
struct Ov008SubitemBlock;
extern void ApplySelectedSubitemValues(int root, struct Ov008SubitemBlock *widget, int useAlt);
extern void SetWidgetRootInputCallback(void *root, u32 callback);
extern void SetOv013WidgetSelectionAWithSound(int context);

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
    ApplyOv013SubitemValuesToWidgets(0);
    UploadOv013SubBg0ScreenEntry1();

    SetEntrySlotsVisible((int)gOv013PanelState->widgets,
                        (int *)FindWidgetById(gOv013PanelState->widgets, 9), 1);
    SetEntrySlotsVisible((int)gOv013PanelState->widgets,
                        (int *)FindWidgetById(gOv013PanelState->widgets, 10), 1);
    ClearWidgetRecordActiveBits(gOv013PanelState->widgets,
                      (const struct WidgetPositionRecord *)(FindWidgetById(gOv013PanelState->widgets, 0)));
    ClearWidgetRecordActiveBits(gOv013PanelState->widgets,
                      (const struct WidgetPositionRecord *)(FindWidgetById(gOv013PanelState->widgets, 2)));
    ClearWidgetRecordActiveBits(gOv013PanelState->widgets,
                      (const struct WidgetPositionRecord *)(FindWidgetById(gOv013PanelState->widgets, 3)));
    root = gOv013PanelState->widgets;
    ApplySelectedSubitemValues((int)root, (struct Ov008SubitemBlock *)FindWidgetById(root, 2), 0);
    root = gOv013PanelState->widgets;
    ApplySelectedSubitemValues((int)root, (struct Ov008SubitemBlock *)FindWidgetById(root, 3), 0);
    SetWidgetRootInputCallback(gOv013PanelState->widgets, (u32)SetOv013WidgetSelectionAWithSound);
    PlaySoundEffect(2, 1);
    root = gOv013PanelState->widgets;
    ClearWidgetRecordActiveBits(root, (const struct WidgetPositionRecord *)(FindWidgetById(root, 5)));
    root = gOv013PanelState->widgets;
    SetWidgetAnimationFrame(root, (const struct WidgetPositionRecord *)(FindWidgetById(root, 5)), 0);
    gOv013PanelState->step = 0;
}
