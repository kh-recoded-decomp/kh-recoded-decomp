#include "nitro/types.h"

typedef struct PanelWidget {
    u8 pad_00[0xc];
    u32 value;
} PanelWidget;

typedef struct PanelState {
    u8 pad_00[3];
    u8 resultMode;
    u8 pad_04[0xc];
    u32 resultValue;
    u8 pad_14[0x9a - 0x14];
    u8 flags;
    u8 pad_9b[0x2bc - 0x9b];
    s32 scrollPixels;
    u8 pad_2c0[0x6818 - 0x2c0];
    u8 panel[4];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void RefreshProgressCaption_0206f06c(void);
extern PanelWidget *FindWidgetById_020b90a4(void *panel, int id);
extern void SetFocusedWidget_020b96e4(void *panel, PanelWidget *widget);
extern void DrawPanelResultCaption_0206f3d8(int mode);
extern void func_ov013_02070e40(int mode);
extern void func_ov013_02070a50(void);
extern void SetEntrySlotsVisible_020b9580(void *panel, PanelWidget *widget, int visible);
extern void func_ov027_020b95e4(void *panel, PanelWidget *widget);
extern void ApplySelectedSubitemValues_020b94fc(void *panel, PanelWidget *widget, int flag);
extern void func_ov027_020b9098(void *panel, void (*callback)(void));
extern void func_ov013_02074420(void);
extern void PlaySoundEffect_0204d924(int id, int flag);
extern void func_ov027_020b96a0(void *panel, PanelWidget *widget, int flag);

void OpenPanelResultMenu_020727b4(void)
{
    u8 *panel;

    data_ov013_02074ce0->flags |= 8;
    RefreshProgressCaption_0206f06c();
    SetFocusedWidget_020b96e4(data_ov013_02074ce0->panel, FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 10));
    data_ov013_02074ce0->resultValue = FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 10)->value;
    DrawPanelResultCaption_0206f3d8(1);
    data_ov013_02074ce0->resultMode = 0;
    data_ov013_02074ce0->scrollPixels = 0;
    data_ov013_02074ce0->resultMode = 0;
    func_ov013_02070e40(0);
    func_ov013_02070a50();
    SetEntrySlotsVisible_020b9580(data_ov013_02074ce0->panel, FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 9), 1);
    SetEntrySlotsVisible_020b9580(data_ov013_02074ce0->panel, FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 10), 1);
    func_ov027_020b95e4(data_ov013_02074ce0->panel, FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 0));
    func_ov027_020b95e4(data_ov013_02074ce0->panel, FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 2));
    func_ov027_020b95e4(data_ov013_02074ce0->panel, FindWidgetById_020b90a4(data_ov013_02074ce0->panel, 3));
    panel = data_ov013_02074ce0->panel;
    ApplySelectedSubitemValues_020b94fc(panel, FindWidgetById_020b90a4(panel, 2), 0);
    panel = data_ov013_02074ce0->panel;
    ApplySelectedSubitemValues_020b94fc(panel, FindWidgetById_020b90a4(panel, 3), 0);
    func_ov027_020b9098(data_ov013_02074ce0->panel, func_ov013_02074420);
    PlaySoundEffect_0204d924(2, 1);
    panel = data_ov013_02074ce0->panel;
    func_ov027_020b95e4(panel, FindWidgetById_020b90a4(panel, 5));
    panel = data_ov013_02074ce0->panel;
    func_ov027_020b96a0(panel, FindWidgetById_020b90a4(panel, 5), 0);
}
