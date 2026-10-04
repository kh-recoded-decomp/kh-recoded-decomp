#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct {
    int nodeIndices[8];
} GroupNodeTable;

typedef struct {
    u8 messages[0xc];
    u8 statsLayer[0x34];
    u8 menuLayer[0x34];
    u8 titleLayer[0x34];
    void *nodes[26];
    u8 pad110[0x24];
    int group;
    int pad138;
    int subPage;
    u8 pad140[0x34];
    u8 screenLayers[0x1c];
} RecordPanel;

extern const TextFrame data_ov086_020c2108;
extern const GroupNodeTable data_ov086_020c226c;
extern const char data_ov086_020c2fd8[];
extern void LoadPackedFileView_020ba25c(RecordPanel *view, const char *path, BOOL fromTail);
extern u16 *UpdateWidgetLayerDefault_020b9df0(u8 *layers, int layerId);
extern void func_ov027_020b9e00(u8 *layers, int layerId);
extern u16 *func_ov039_020bc1e4(int layerId);
extern void *func_ov039_020bc994(void);
extern void InitTextLayerAt_020014b0(void *window, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void *GetWord20_020019f0(void *window);
extern void *func_02001914(void *window, int selectAsCurrent, int alignFromEnd);
extern void *func_ov027_020ba2a8(RecordPanel *panel, int messageId);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const void *text);
extern void SelectListNodeOrFirst_020019b8(void *self, void *target);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern void DrawRecordPanelStats_020bf6ac(RecordPanel *panel);
extern void func_ov086_020bfb80(RecordPanel *panel);
extern void DrawCounterGoalText_020bfbe0(RecordPanel *panel);
extern void DrawSecondCounterText_020bfd0c(RecordPanel *panel);

void InitRecordPanelText_020c1078(RecordPanel *panel)
{
    TextFrame frame = data_ov086_020c2108;
    GroupNodeTable table;
    u16 *screen;
    int i;
    int group;
    int first;
    int nodeIndex;
    int sub;

    i = 0;
    LoadPackedFileView_020ba25c(panel, data_ov086_020c2fd8, FALSE);
    InitTextLayerAt_020014b0(panel->statsLayer, 5, UpdateWidgetLayerDefault_020b9df0(panel->screenLayers, 0x19), func_ov039_020bc994(), &frame);
    func_ov027_020b9e00(panel->screenLayers, 0x19);
    screen = func_ov039_020bc1e4(0x18);
    frame.x = 1;
    frame.y = 0;
    frame.charBase = 1;
    frame.width = 0xb;
    frame.height = 2;
    InitTextLayerAt_020014b0(panel->menuLayer, 4, screen, func_ov039_020bc994(), &frame);
    panel->nodes[19] = GetWord20_020019f0(panel->menuLayer);
    DrawTextAnchored_020015a0(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2a8(panel, 10));
    panel->nodes[20] = func_02001914(panel->menuLayer, 1, 0);
    DrawTextAnchored_020015a0(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2a8(panel, 9));
    for (; i < 3; i++) {
        panel->nodes[21 + i] = func_02001914(panel->menuLayer, 1, 0);
        DrawTextAnchored_020015a0(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2a8(panel, i + 0xb));
    }
    panel->nodes[24] = func_02001914(panel->menuLayer, 1, 0);
    DrawTextAnchored_020015a0(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2a8(panel, 0x18));
    panel->nodes[25] = func_02001914(panel->menuLayer, 1, 0);
    DrawTextAnchored_020015a0(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2a8(panel, 0x19));
    frame.x = 0xc;
    frame.y = 0x13;
    frame.width = 0x13;
    frame.height = 5;
    frame.charBase += 0x16;
    InitTextLayerAt_020014b0(panel->titleLayer, 4, screen, func_ov039_020bc994(), &frame);
    DrawTextAnchored_020015a0(panel->titleLayer, 0, 0, 2, 0x209, func_ov027_020ba2a8(panel, 0));
    table = data_ov086_020c226c;
    first = table.nodeIndices[0];
    panel->nodes[first] = GetWord20_020019f0(panel->statsLayer);
    DrawRecordPanelStats_020bf6ac(panel);
    for (group = 1; group < 8; group++) {
        panel->group = group;
        panel->nodes[table.nodeIndices[group]] = func_02001914(panel->statsLayer, 1, 0);
        DrawRecordPanelStats_020bf6ac(panel);
    }
    for (group = 0; group < 8; group++) {
        panel->group = group;
        panel->subPage = 1;
        nodeIndex = table.nodeIndices[group];
        panel->nodes[nodeIndex + 1] = func_02001914(panel->statsLayer, 1, 0);
        if (group == 7) {
            DrawSecondCounterText_020bfd0c(panel);
        } else {
            func_ov086_020bfb80(panel);
            if (group == 3) {
                for (sub = 2; sub < 4; sub++) {
                    panel->subPage = sub;
                    panel->nodes[nodeIndex + sub] = func_02001914(panel->statsLayer, 1, 0);
                    func_ov086_020bfb80(panel);
                }
            } else if (group == 6) {
                func_ov086_020bfb80(panel);
                panel->subPage = 2;
                panel->nodes[16] = func_02001914(panel->statsLayer, 1, 0);
                DrawCounterGoalText_020bfbe0(panel);
            }
        }
    }
    panel->group = 0;
    panel->subPage = 0;
    SelectListNodeOrFirst_020019b8(panel->statsLayer, panel->nodes[first]);
    Text_UploadTileBuffer_02001520(panel->menuLayer);
}
