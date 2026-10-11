#include "nitro/types.h"

typedef struct PanelTextSurface {
    u8 unknown00[0x20];
    void *vramTarget;
    void *tileBuffer;
    int uploadParam;
    u16 rowSize;
    u8 unknown2e[4];
    u8 rowCount;
} PanelTextSurface;

typedef struct TwoChoicePanelText {
    u8 selectedChoice;
    u8 enabledChoices;
    u16 unknown02;
    PanelTextSurface title;
    PanelTextSurface choices;
    PanelTextSurface description;
    const u16 *labels[2];
    const u16 *descriptions[2];
} TwoChoicePanelText;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void DrawTextAnchored(PanelTextSurface *surface, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextColored(PanelTextSurface *surface, int x, int y, int color, int altColor, const u16 *text);
extern void Text_UploadTileBuffer(PanelTextSurface *surface);

void RefreshTwoChoicePanelText(TwoChoicePanelText *panel)
{
    s16 i = 0;
    CallVirtualHandlerSlot1(&panel->choices, 0);
    CallVirtualHandlerSlot1(&panel->description, 0);
    for (; i < 2; i++) {
        const u16 *label = panel->labels[i];
        int color = ((1 << i) & panel->enabledChoices) ? 2 : 4;
        int x = (i == panel->selectedChoice) ? 8 : 0;
        DrawTextAnchored(&panel->choices, x, 24 * i + 11, color, 8, label);
    }
    DrawTextColored(&panel->description, 2, 0, 2, 10, panel->descriptions[panel->selectedChoice]);
    Text_UploadTileBuffer(&panel->choices);
    Text_UploadTileBuffer(&panel->description);
    Text_UploadTileBuffer(&panel->title);
}
