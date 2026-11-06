#include "src/overlays/ov027/WidgetRecordOps.h"
#pragma opt_propagation on
#pragma opt_common_subs on
#include "nitro/types.h"
#include "src/overlays/ov015/WirelessMenuContext.h"
#include "src/overlays/ov015/WirelessBoardData.h"

extern WirelessMenuContext *gWirelessMenuWork;
extern int DispatchContextCommand(int query, int a, int b, int c);
extern void DrawPanelInfoText(void);
extern BOOL PlaySoundEffect(int group, int sound);
extern void *FindWidgetById(void *manager, int id);

void HandleWirelessPanelNavigation(WidgetPositionRecord *widget, u32 keys)
{
    WidgetPoint position;
    s8 selectedType;
    WirelessMenuContext *volatile *contextSlot;
    u8 previousFocus;
    int delta;
    delta = 0;
    previousFocus = gWirelessMenuWork->focusMode;
    ResolveWidgetPositionComponents(gWirelessMenuWork->widgetManager,
                                   widget, &position, WIDGET_POSITION_COMBINED_XY);
    switch (widget->id) {
    case 4: {
        WirelessMenuContext *context;
        int choiceIndex;
        if (keys & 0x40)
            delta--;
        if (keys & 0x80)
            delta++;
        gWirelessMenuWork->choiceIndex += (s8)delta;
        context = gWirelessMenuWork;
        choiceIndex = context->choiceIndex;
        if (choiceIndex >=
            (s32)gWirelessRandomChoiceLimits[DispatchContextCommand(6, 0, 0, 0)]) {
            context->choiceIndex = 0;
        } else if (choiceIndex < 0) {
            gWirelessMenuWork->choiceIndex =
                gWirelessRandomChoiceLimits[DispatchContextCommand(6, 0, 0, 0)] - 1;
        }
        contextSlot = (WirelessMenuContext *volatile *)&gWirelessMenuWork;
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
        gWirelessMenuWork->focusMode = 1;
        position.x -= 0x2c000;
        break;
    case 10:
        if (keys & 0x40)
            delta--;
        if (keys & 0x80)
            delta++;
        gWirelessMenuWork->choiceType += (s8)delta;
        selectedType = gWirelessMenuWork->choiceType;
        if (gWirelessMenuWork->choiceType >= 6)
            gWirelessMenuWork->choiceType = 0;
        else if (selectedType < 0)
            gWirelessMenuWork->choiceType = 5;
        if (delta != 0) {
            WirelessMenuContext *context = gWirelessMenuWork;
            void *manager = context->widgetManager;
            void *choiceWidget = FindWidgetById(manager, 10);
            SetWidgetAnimationFrame(manager, (const struct WidgetPositionRecord *)(choiceWidget), context->choiceType);
            PlaySoundEffect(2, 1);
        }
        gWirelessMenuWork->focusMode = 0;
        position.x -= 0x19000;
        break;
    }
    {
        void *cursor = FindWidgetById(gWirelessMenuWork->widgetManager, 11);
        SetWidgetPosition(gWirelessMenuWork->widgetManager,
                           cursor, &position, 0);
    }
    if (previousFocus != gWirelessMenuWork->focusMode)
        PlaySoundEffect(2, 0);
}
