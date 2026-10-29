#pragma opt_propagation on
#pragma opt_common_subs on
#include "nitro/types.h"
#include "src/overlays/ov015/WirelessMenuContext.h"
#include "src/overlays/ov015/WirelessBoardData.h"

extern WirelessMenuContext *data_ov015_0207e960;
extern int DispatchContextCommand(int query, int a, int b, int c);
extern void DrawPanelInfoText(void);
extern BOOL PlaySoundEffect(int group, int sound);
extern void *FindWidgetById(void *manager, int id);
extern void func_ov027_020b96c0(void *manager, void *widget, int mode);

void HandleWirelessPanelNavigation(WidgetPositionRecord *widget, u32 keys)
{
    WidgetPoint position;
    s8 selectedType;
    WirelessMenuContext *volatile *contextSlot;
    u8 previousFocus;
    int delta;
    delta = 0;
    previousFocus = data_ov015_0207e960->focusMode;
    ResolveWidgetPositionComponents(data_ov015_0207e960->widgetManager,
                                   widget, &position, WIDGET_POSITION_COMBINED_XY);
    switch (widget->id) {
    case 4: {
        WirelessMenuContext *context;
        int choiceIndex;
        if (keys & 0x40)
            delta--;
        if (keys & 0x80)
            delta++;
        data_ov015_0207e960->choiceIndex += (s8)delta;
        context = data_ov015_0207e960;
        choiceIndex = context->choiceIndex;
        if (choiceIndex >=
            (s32)gWirelessRandomChoiceLimits[DispatchContextCommand(6, 0, 0, 0)]) {
            context->choiceIndex = 0;
        } else if (choiceIndex < 0) {
            data_ov015_0207e960->choiceIndex =
                gWirelessRandomChoiceLimits[DispatchContextCommand(6, 0, 0, 0)] - 1;
        }
        contextSlot = (WirelessMenuContext *volatile *)&data_ov015_0207e960;
        if (delta != 0) {
            DrawPanelInfoText();
            PlaySoundEffect(2, 1);
        }
        {
            /* Commit the cursor coordinates before the ordered focus change. */
            fx32 y;
            fx32 x;
            x = *(volatile fx32 *)&position.x;
            y = position.y;
            x -= 0x34000;
            y -= 0x19000;
            *(volatile fx32 *)&position.x = x;
            *(volatile fx32 *)&position.y = y;
        }
        (*contextSlot)->focusMode = 2;
        break;
    }
    case 9:
        data_ov015_0207e960->focusMode = 1;
        position.x -= 0x2c000;
        break;
    case 10:
        if (keys & 0x40)
            delta--;
        if (keys & 0x80)
            delta++;
        data_ov015_0207e960->choiceType += (s8)delta;
        selectedType = data_ov015_0207e960->choiceType;
        if (data_ov015_0207e960->choiceType >= 6)
            data_ov015_0207e960->choiceType = 0;
        else if (selectedType < 0)
            data_ov015_0207e960->choiceType = 5;
        if (delta != 0) {
            WirelessMenuContext *context = data_ov015_0207e960;
            void *manager = context->widgetManager;
            void *choiceWidget = FindWidgetById(manager, 10);
            func_ov027_020b96c0(manager, choiceWidget, context->choiceType);
            PlaySoundEffect(2, 1);
        }
        data_ov015_0207e960->focusMode = 0;
        position.x -= 0x19000;
        break;
    }
    {
        void *cursor = FindWidgetById(data_ov015_0207e960->widgetManager, 11);
        func_ov027_020b91e8(data_ov015_0207e960->widgetManager,
                           cursor, &position, 0);
    }
    if (previousFocus != data_ov015_0207e960->focusMode)
        PlaySoundEffect(2, 0);
}
